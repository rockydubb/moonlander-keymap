# build.sh

One-command local build for the Moonlander keymap.

## Usage

```bash
# Default: fetch latest Oryx layout + build
./build.sh

# Build only, without fetching from Oryx (use when you've edited
# nvWgW/keymap.c directly and don't want Oryx to overwrite your changes)
./build.sh qmk

# Build and flash from the terminal with Zapp
./build.sh flash

# Build and open Keymapp as a GUI fallback
./build.sh keymapp
```

## Commands

| Command | What it does |
|---|---|
| `./build.sh` | Fetch Oryx → build → drop .bin in repo root |
| `./build.sh qmk` | Build only (no Oryx fetch) — keeps local QMK edits |
| `./build.sh flash` | Fetch Oryx → build → flash with Zapp |
| `./build.sh keymapp` | Fetch Oryx → build → open Keymapp |
| `./build.sh fetch` | Same as no args (alias) |

## What it does (in order)

1. **Fetch Oryx layout** (skipped with `qmk`): calls ZSA's GraphQL
   API for the latest revision of your layout, downloads the source
   zip, extracts it into `nvWgW/`. This OVERWRITES `keymap.c` with
   Oryx's freshly-regenerated content.
2. **Ensure ZSA QMK source** is present: clones `zsa/qmk_firmware` at
   the latest `firmware<N>` branch (only on first run, or if
   `qmk_firmware/` was deleted).
3. **Copy keymap** into the QMK build tree (`qmk_firmware/keyboards/
   zsa/moonlander/keymaps/nvWgW/`).
4. **Compile** with `qmk compile -kb zsa/moonlander/reva -km nvWgW`.
5. **Drop .bin** in two places: `qmk_firmware/` (QMK's default) and
   the repo root (for easy access by Keymapp's firmware picker).
6. **Flash with Zapp** when using `./build.sh flash`: runs
   `zapp flash zsa_moonlander_reva_nvWgW.bin` and waits for the
   Moonlander to enter bootloader mode.

## Output

The compiled firmware is at:
```
zsa_moonlander_reva_nvWgW.bin   (repo root, what you flash)
qmk_firmware/zsa_moonlander_reva_nvWgW.bin   (QMK's default location)
```

Both are the same file (the script copies after building).

## Why the Oryx fetch is the default

Rocky's workflow is 95% editing in Oryx. After clicking "Compile this
layout" in Oryx, the next `./build.sh` should pull those changes and
build. The `qmk` opt-out exists for the rare case where you've
edited QMK code directly in `nvWgW/keymap.c` and want to build
without the Oryx fetch overwriting your changes.

## Why pin a specific ZSA QMK version?

ZSA Oryx produces a `keymap.c` that targets a specific QMK firmware
version. If you build with a newer QMK, the keymap might fail to
compile. The action and the build script both pin to whatever version
Oryx last used (`firmware<N>` branch on zsa/qmk_firmware).

## Requirements

- `qmk` CLI in `$PATH` (`brew install qmk/qmk/qmk`)
- `arm-none-eabi-gcc` (installed automatically by `qmk setup`)
- `git`
- `jq` (for the Oryx fetch step)
- `zapp` for `./build.sh flash` (`brew install zapp`)
- Internet access on first run (to clone zsa/qmk_firmware and fetch
  the Oryx layout)

## Updating the ZSA QMK version

Just delete the `qmk_firmware/` directory and re-run `./build.sh`. It
will re-clone at the latest version.

## Troubleshooting

### "Cannot index object with number" on Oryx fetch

jq parsing error. Usually means the layout ID is wrong, or Oryx's
GraphQL response structure changed. Check the `ORYX_LAYOUT_ID` env
var or the default in `build.sh` (default: `nvWgW`). The layout ID is
in the URL of your Oryx layout:
`https://configure.zsa.io/moonlander/layouts/YOUR_ID/latest`

### Build fails with "Module 'zsa/oryx' not found"

You're building against the wrong QMK source. `qmk_firmware/` should
be ZSA's fork, not the generic `qmk/qmk_firmware`. Delete
`qmk_firmware/` and re-run `./build.sh`.

### Animations disappeared after running `./build.sh`

Oryx regenerated `keyboard_post_init_user()` and removed the RGB
animation block. Re-apply the snippet (see `docs/custom-features.md`),
then run `./build.sh qmk` to build without re-fetching.

### `zapp: command not found`

Install Zapp:

```bash
brew install zapp
```

Then re-run:

```bash
./build.sh flash
```
