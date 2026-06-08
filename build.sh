#!/usr/bin/env bash
# Build the Moonlander keymap locally.
# Requires: qmk CLI, arm-none-eabi-gcc, git, curl, jq, python3.
# First run only: this script will clone zsa/qmk_firmware into ./qmk_firmware
# (it's gitignored, so it'll need to be re-cloned on a fresh checkout).
#
# Usage:
#   ./build.sh             # build only
#   ./build.sh fetch       # fetch latest Oryx layout, then build
#   ./build.sh flash       # build and open Keymapp for flashing

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
KEYMAP="nvWgW"
GEOMETRY="zsa/moonlander/reva"
QMK_FW_DIR="$SCRIPT_DIR/qmk_firmware"
ZSA_QMK_REPO="https://github.com/zsa/qmk_firmware.git"
ZSA_ORYX_GRAPHQL="https://oryx.zsa.io/graphql"

# Default layout id and geometry — match your .github/workflows/fetch-and-build-layout.yml
ORYX_LAYOUT_ID="${ORYX_LAYOUT_ID:-nvWgW}"
ORYX_GEOMETRY="${ORYX_GEOMETRY:-moonlander/reva}"

###############################
# Step 1: fetch latest Oryx layout
###############################
fetch_oryx() {
  echo ""
  echo "▶ Fetching latest Oryx layout for ${ORYX_LAYOUT_ID} (${ORYX_GEOMETRY})..."

  if ! command -v jq >/dev/null 2>&1; then
    echo "ERROR: jq is required for Oryx fetch. Install with: brew install jq" >&2
    exit 1
  fi

  # Query ZSA's GraphQL API for the latest revision of this layout
  local response
  response=$(curl --location --silent --show-error \
    "$ZSA_ORYX_GRAPHQL" \
    --header 'Content-Type: application/json' \
    --data "{\"query\":\"query getLayout(\$hashId: String!, \$revisionId: String!, \$geometry: String) {layout(hashId: \$hashId, geometry: \$geometry, revisionId: \$revisionId) {  revision { hashId, qmkVersion, title }}}\",\"variables\":{\"hashId\":\"${ORYX_LAYOUT_ID}\",\"geometry\":\"${ORYX_GEOMETRY}\",\"revisionId\":\"latest\"}}")

  # Convert the revision object to a 3-element array: [hashId, qmkVersion, title]
  local revision_array
  revision_array=$(echo "${response}" | jq '.data.layout.revision | [.hashId, .qmkVersion, .title]')
  if [[ -z "${revision_array}" || "${revision_array}" == "null" ]]; then
    echo "ERROR: could not fetch Oryx layout. Response was:" >&2
    echo "${response}" >&2
    exit 1
  fi

  local hash_id firmware_version change_description
  hash_id=$(echo "${revision_array}" | jq -r '.[0]')
  firmware_version=$(echo "${revision_array}" | jq -r '.[1]')
  change_description=$(echo "${revision_array}" | jq -r '.[2]')

  if [[ -z "${hash_id}" || "${hash_id}" == "null" ]]; then
    echo "ERROR: could not fetch Oryx layout. Response was:" >&2
    echo "${response}" >&2
    exit 1
  fi

  if [[ -z "${change_description}" || "${change_description}" == "null" ]]; then
    change_description="latest layout modification made with Oryx"
  fi
  firmware_version=$(printf "%.0f" "${firmware_version}")

  echo "  hash_id=${hash_id}, firmware_version=${firmware_version}"
  echo "  description: ${change_description}"

  # Download the source zip
  local tmp_zip
  tmp_zip="$(mktemp -t oryx-source)"
  curl --location --silent --show-error --output "${tmp_zip}" "https://oryx.zsa.io/source/${hash_id}"

  # Unzip into the keymap folder
  echo "  Unzipping into ${KEYMAP}/..."
  # Oryx source zips contain a single folder like *_source/ — flatten it
  local tmp_dir
  tmp_dir="$(mktemp -d)"
  unzip -q "${tmp_zip}" -d "${tmp_dir}"
  # Find the *_source subfolder
  local source_dir
  source_dir=$(find "${tmp_dir}" -maxdepth 2 -type d -name '*_source' | head -1)
  if [[ -z "${source_dir}" ]]; then
    echo "ERROR: could not find *_source folder in Oryx zip" >&2
    exit 1
  fi
  # Copy files into the keymap folder, overwriting but keeping any local files
  # not in the zip (e.g. autocorrect_dict.txt)
  cp -r "${source_dir}/." "${SCRIPT_DIR}/${KEYMAP}/"

  # Re-apply custom QMK snippets that Oryx's regeneration wiped out
  # (RGB animation on boot, DANCE_1 tap dance for the left thumb 3rd
  # button, etc.). The script is idempotent — re-running it does
  # nothing if the patches are already in place.
  echo "  Applying custom QMK patches..."
  python3 patches/apply_patches.py

  rm -rf "${tmp_zip}" "${tmp_dir}"
  echo "  ✓ Oryx layout fetched and merged into ${KEYMAP}/"
}

###############################
# Step 2: ensure ZSA QMK source is present
###############################
ensure_qmk_firmware() {
  # Detect latest firmware<N> branch from ZSA fork
  echo ""
  echo "▶ Detecting latest ZSA QMK firmware version..."
  local latest_version
  latest_version=$(git ls-remote --heads "$ZSA_QMK_REPO" 2>/dev/null \
    | awk -F'/' '{print $NF}' \
    | grep -E '^firmware[0-9]+$' \
    | sort -V \
    | tail -1 \
    | sed 's/firmware//')

  if [[ -z "$latest_version" ]]; then
    echo "ERROR: could not detect latest firmware version. Check network access." >&2
    exit 1
  fi
  echo "  Latest version: $latest_version"

  # Clone qmk_firmware if missing
  if [[ ! -d "$QMK_FW_DIR/quantum" ]]; then
    echo "  Cloning zsa/qmk_firmware (branch firmware${latest_version})..."
    rm -rf "$QMK_FW_DIR"
    git clone --depth=1 --branch "firmware${latest_version}" "$ZSA_QMK_REPO" "$QMK_FW_DIR"
    (cd "$QMK_FW_DIR" && git submodule update --init --depth=1)
  else
    echo "  qmk_firmware/ already present"
  fi
}

###############################
# Step 3: copy keymap into build tree
###############################
copy_keymap() {
  echo ""
  echo "▶ Copying ${KEYMAP}/ into QMK build tree..."
  rm -rf "$QMK_FW_DIR/keyboards/zsa/moonlander/keymaps/$KEYMAP"
  mkdir -p "$QMK_FW_DIR/keyboards/zsa/moonlander/keymaps"
  cp -r "$SCRIPT_DIR/$KEYMAP" "$QMK_FW_DIR/keyboards/zsa/moonlander/keymaps/"
}

###############################
# Step 4: build
###############################
do_build() {
  echo ""
  echo "▶ Building ${GEOMETRY}:${KEYMAP}..."
  (cd "$QMK_FW_DIR" && qmk compile -kb zsa/moonlander/reva -km "$KEYMAP")

  local bin_path="$QMK_FW_DIR/zsa_moonlander_reva_${KEYMAP}.bin"
  if [[ -f "$bin_path" ]]; then
    echo ""
    echo "✓ Built: $bin_path"
    # Also copy to repo root for easy access
    cp "$bin_path" "$SCRIPT_DIR/zsa_moonlander_reva_${KEYMAP}.bin"
    echo "  Also copied to: $SCRIPT_DIR/zsa_moonlander_reva_${KEYMAP}.bin"
  else
    echo "ERROR: build succeeded but .bin not found at $bin_path" >&2
    exit 1
  fi
}

###############################
# Step 5: open Keymapp
###############################
do_flash() {
  local bin_path="$SCRIPT_DIR/zsa_moonlander_reva_${KEYMAP}.bin"
  if [[ ! -f "$bin_path" ]]; then
    echo "ERROR: $bin_path not found. Run ./build.sh first." >&2
    exit 1
  fi
  echo ""
  echo "▶ Opening Keymapp..."
  if open -a "Keymapp" 2>/dev/null; then
    echo "  ✓ Keymapp opened. Drag $bin_path into the window."
  else
    echo "  Keymapp not found — opening the .bin directly."
    open "$bin_path"
  fi
}

###############################
# Main
###############################
# Default behavior: build only, using the local keymap you have on disk.
# Pass "fetch" to pull the latest Oryx layout first (this OVERWRITES the
# local keymap.c with the Oryx-emitted version, so any local customizations
# to keymap.c will be lost unless you re-apply them after the fetch).
# Pass "flash" to also open Keymapp after the build.
#
# Workflow recommendation:
#   - Edit in Oryx web UI -> compile -> run `./build.sh fetch` (re-fetches
#     the keymap, may need rebase/merge) -> run `./build.sh` (builds).
#   - For QMK-specific tweaks (custom keycodes, RGB effects, etc.) that
#     Oryx doesn't support, edit nvWgW/keymap.c directly and run
#     `./build.sh` WITHOUT `fetch` so your edits aren't overwritten.
case "${1:-}" in
  "")
    fetch_oryx
    ensure_qmk_firmware
    copy_keymap
    do_build
    ;;
  build)
    ensure_qmk_firmware
    copy_keymap
    do_build
    ;;
  qmk)
    # Build without fetching from Oryx — use this when you've edited
    # QMK code (custom keycodes, RGB tweaks, etc.) directly in
    # nvWgW/keymap.c and don't want Oryx to overwrite your changes.
    ensure_qmk_firmware
    copy_keymap
    do_build
    ;;
  fetch)
    fetch_oryx
    ensure_qmk_firmware
    copy_keymap
    do_build
    ;;
  flash)
    fetch_oryx
    ensure_qmk_firmware
    copy_keymap
    do_build
    do_flash
    ;;
  *)
    echo "Usage: $0 [build|qmk|fetch|flash]"
    echo ""
    echo "  no args    - Fetch latest Oryx layout + build (DEFAULT — use after editing in Oryx)"
    echo "  build      - Same as no args (alias)"
    echo "  qmk        - Build WITHOUT fetching from Oryx (use after editing QMK code directly)"
    echo "  fetch      - Same as no args (alias)"
    echo "  flash      - Fetch Oryx + build + open Keymapp"
    exit 1
    ;;
esac
