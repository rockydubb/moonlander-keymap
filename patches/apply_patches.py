#!/usr/bin/env python3
"""
apply_patches.py — re-apply custom QMK snippets to nvWgW files after
Oryx syncs have wiped them.

Each patch is a (marker, snippet) pair:
- `marker` is a unique string already in the Oryx-emitted file
  (or empty if there isn't one — patch is then applied unconditionally
  if `expected` snippet text is not already present)
- `snippet` is the C code to insert

Patches are applied via literal string find-and-replace. The script
is idempotent: running it twice does nothing on the second run.
"""

import sys
import re
from pathlib import Path

KEYMAP_DIR = Path(__file__).parent.parent / "nvWgW"
KEYMAP_C = KEYMAP_DIR / "keymap.c"
RULES_MK = KEYMAP_DIR / "rules.mk"


# Each patch: (description, find, replace, require_match)
# - If `require_match` is True, the patch is applied unconditionally
#   (used when find is unique enough).
# - If False, the patch is only applied if `find` exists in the file
#   AND `replace` does NOT already exist in the file (idempotent guard).
PATCHES = [
    # --------------------------------------------------------------
    # Patch 1: Force RGB animation on boot in keyboard_post_init_user()
    # This block gets wiped by Oryx regeneration, so we re-add it.
    # --------------------------------------------------------------
    {
        "description": "Force RGB animation on boot (disable Oryx ledmap[] override)",
        "find": "void keyboard_post_init_user(void) {\n  rgb_matrix_enable();\n}",
        "replace": """void keyboard_post_init_user(void) {
  // Force RGB animation on layer 0, bypassing the Oryx ledmap[] static
  // colors. The Oryx keymap sets up a static color override for each
  // layer, which clobbers any QMK animation effect on every matrix scan.
  // By disabling layer-LED overrides and forcing a specific animation
  // mode at boot, the user can use the "Switch ANI" / "Animation" key
  // (RGB_MODE_FORWARD) to cycle through QMK animation effects.
  // This snippet is re-applied by patches/apply_patches.py after Oryx syncs.
  keyboard_config.disable_layer_led = true;
  eeconfig_update_kb(keyboard_config.raw);
  autocorrect_enable();
  rgb_matrix_enable_noeeprom();
  rgb_matrix_mode_noeeprom(6);  // CYCLE_LEFT_RIGHT (rainbow sweep)
}""",
        "idempotency_check": "autocorrect_enable();",
    },
    # --------------------------------------------------------------
    # Patch 2: Autocorrect toggle key
    # Oryx can regenerate layer 1 with F11 in this slot. Keep the
    # firmware-level autocorrect toggle in that stable position.
    # --------------------------------------------------------------
    {
        "description": "Map layer 1 top-right key to AC_TOGG",
        "path": KEYMAP_C,
        "find": "KC_F10,         KC_F11,",
        "replace": "KC_F10,         AC_TOGG,",
        "idempotency_check": "KC_F10,         AC_TOGG,",
    },
    # --------------------------------------------------------------
    # Patch 3: Autocorrect feature flag
    # Keep AUTOCORRECT_ENABLE on even when Oryx rewrites rules.mk.
    # --------------------------------------------------------------
    {
        "description": "Enable QMK Autocorrect",
        "path": RULES_MK,
        "find": "CAPS_WORD_ENABLE = yes\n",
        "replace": "CAPS_WORD_ENABLE = yes\nAUTOCORRECT_ENABLE = yes\n",
        "idempotency_check": "AUTOCORRECT_ENABLE = yes",
    },
    # --------------------------------------------------------------
    # Patch 4: Feed Oryx custom tap letters into Autocorrect
    # Oryx's generated DUAL_FUNC handlers send letters manually with
    # register_code16() and return false, which stops QMK's normal
    # process_autocorrect() pass from seeing those letters. Feed the
    # tapped letter into Autocorrect before sending it to the host.
    # --------------------------------------------------------------
    {
        "description": "Add helper for Autocorrect on Oryx custom tap letters",
        "path": KEYMAP_C,
        "find": "bool process_record_user(uint16_t keycode, keyrecord_t *record) {\n",
        "replace": """static void process_autocorrect_for_custom_keycode(uint16_t keycode, keyrecord_t *record) {
#ifdef AUTOCORRECT_ENABLE
  process_autocorrect(keycode, record);
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
""",
        "idempotency_check": "process_autocorrect_for_custom_keycode",
    },
    {
        "description": "Feed DUAL_FUNC_0 tap letter into Autocorrect",
        "path": KEYMAP_C,
        "find": "          register_code16(KC_F);\n",
        "replace": "          process_autocorrect_for_custom_keycode(KC_F, record);\n          register_code16(KC_F);\n",
        "idempotency_check": "process_autocorrect_for_custom_keycode(KC_F, record);",
    },
    {
        "description": "Feed DUAL_FUNC_1 tap letter into Autocorrect",
        "path": KEYMAP_C,
        "find": "          register_code16(KC_Z);\n",
        "replace": "          process_autocorrect_for_custom_keycode(KC_Z, record);\n          register_code16(KC_Z);\n",
        "idempotency_check": "process_autocorrect_for_custom_keycode(KC_Z, record);",
    },
    {
        "description": "Feed DUAL_FUNC_2 tap letter into Autocorrect",
        "path": KEYMAP_C,
        "find": "          register_code16(KC_X);\n",
        "replace": "          process_autocorrect_for_custom_keycode(KC_X, record);\n          register_code16(KC_X);\n",
        "idempotency_check": "process_autocorrect_for_custom_keycode(KC_X, record);",
    },
    {
        "description": "Feed DUAL_FUNC_3 tap letter into Autocorrect",
        "path": KEYMAP_C,
        "find": "          register_code16(KC_C);\n",
        "replace": "          process_autocorrect_for_custom_keycode(KC_C, record);\n          register_code16(KC_C);\n",
        "idempotency_check": "process_autocorrect_for_custom_keycode(KC_C, record);",
    },
    {
        "description": "Feed DUAL_FUNC_4 tap letter into Autocorrect",
        "path": KEYMAP_C,
        "find": "          register_code16(KC_V);\n",
        "replace": "          process_autocorrect_for_custom_keycode(KC_V, record);\n          register_code16(KC_V);\n",
        "idempotency_check": "process_autocorrect_for_custom_keycode(KC_V, record);",
    },
    {
        "description": "Feed DUAL_FUNC_7 tap letter into Autocorrect",
        "path": KEYMAP_C,
        "find": "          register_code16(KC_P);\n",
        "replace": "          process_autocorrect_for_custom_keycode(KC_P, record);\n          register_code16(KC_P);\n",
        "idempotency_check": "process_autocorrect_for_custom_keycode(KC_P, record);",
    },
]


def apply_patches():
    contents = {}
    original_contents = {}
    for path in {patch.get("path", KEYMAP_C) for patch in PATCHES}:
        if not path.exists():
            print(f"ERROR: {path} not found", file=sys.stderr)
            return 1
        contents[path] = path.read_text()
        original_contents[path] = contents[path]

    applied = []
    skipped = []

    for patch in PATCHES:
        path = patch.get("path", KEYMAP_C)
        content = contents[path]

        # Idempotency check: if the replacement is already in the file, skip
        if "idempotency_check" in patch and patch["idempotency_check"] in content:
            skipped.append(patch["description"])
            continue

        # If the find string doesn't exist, the patch can't apply
        if patch["find"] not in content:
            skipped.append(f"{patch['description']} (find string not found — Oryx may have changed the surrounding code)")
            continue

        contents[path] = content.replace(patch["find"], patch["replace"], 1)
        applied.append(patch["description"])

    changed_paths = [path for path, content in contents.items() if content != original_contents[path]]
    if changed_paths:
        for path in changed_paths:
            path.write_text(contents[path])
        print(f"Applied {len(applied)} patch(es):")
        for desc in applied:
            print(f"  ✓ {desc}")
    else:
        print("No patches needed (all already applied or no matches found)")

    if skipped:
        print(f"\nSkipped {len(skipped)} patch(es):")
        for desc in skipped:
            print(f"  - {desc}")

    return 0


if __name__ == "__main__":
    sys.exit(apply_patches())
