#!/usr/bin/env python3
"""
apply_patches.py — re-apply custom QMK snippets to nvWgW/keymap.c
after Oryx syncs have wiped them.

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

KEYMAP_C = Path(__file__).parent.parent / "nvWgW" / "keymap.c"


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
  rgb_matrix_enable_noeeprom();
  rgb_matrix_mode_noeeprom(6);  // CYCLE_LEFT_RIGHT (rainbow sweep)
}""",
        "idempotency_check": "rgb_matrix_mode_noeeprom(6);",
    },
    # --------------------------------------------------------------
    # Patch 2: Add DANCE_1 to enum
    # --------------------------------------------------------------
    {
        "description": "Add DANCE_1 to tap_dance_codes enum",
        "find": "enum tap_dance_codes {\n  DANCE_0,\n};",
        "replace": "enum tap_dance_codes {\n  DANCE_0,\n  DANCE_1,\n};",
        "idempotency_check": "  DANCE_1,\n};",
    },
    # --------------------------------------------------------------
    # Patch 3: Replace left thumb 3rd button (KC_LEFT_GUI) with TD(DANCE_1)
    # --------------------------------------------------------------
    {
        "description": "Wire left thumb 3rd button to TD(DANCE_1)",
        "find": "KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT_GUI,                    KC_LEFT_ALT,    KC_TAB,         KC_SPACE",
        "replace": "KC_LEFT_GUI,    KC_LEFT_ALT,    TD(DANCE_1),                    KC_LEFT_ALT,    KC_TAB,         KC_SPACE",
        "idempotency_check": "TD(DANCE_1),                    KC_LEFT_ALT,    KC_TAB,         KC_SPACE",
    },
    # --------------------------------------------------------------
    # Patch 4: Resize dance_state array to hold 2 dances
    # --------------------------------------------------------------
    {
        "description": "Resize dance_state array to size 2",
        "find": "static tap dance_state[1];",
        "replace": "static tap dance_state[2];",
        "idempotency_check": "static tap dance_state[2];",
    },
    # --------------------------------------------------------------
    # Patch 5: Add DANCE_1 function bodies + register in actions array
    # This is the big one — the function definitions + the tap_dance_actions entry.
    # --------------------------------------------------------------
    {
        "description": "Add DANCE_1 function bodies and register in tap_dance_actions",
        "find": "tap_dance_action_t tap_dance_actions[] = {\n        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),\n};",
        "replace": """void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

// DANCE_1 — left thumb 3rd button
//   single tap       = Hyper (Cmd+Ctrl+Shift+Alt, all 4)
//   single hold      = Hyper held down
//   double tap       = Hyper (same)
//   double tap+hold  = Ctrl+Shift+Option held + momentary switch to layer 1
//   release from any = back to base state
// Re-applied by patches/apply_patches.py after Oryx syncs.
void on_dance_1(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 3) {
        tap_code16(KC_HYPR);
    }
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP:
        case SINGLE_HOLD:
        case DOUBLE_TAP:
            register_code16(KC_HYPR);
            break;
        case DOUBLE_HOLD:
            register_mods(MOD_LCTL | MOD_LSFT | MOD_LALT);
            layer_on(1);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_HYPR);
            register_code16(KC_HYPR);
            break;
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP:
        case SINGLE_HOLD:
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_HYPR);
            break;
        case DOUBLE_HOLD:
            unregister_mods(MOD_LCTL | MOD_LSFT | MOD_LALT);
            layer_off(1);
            break;
    }
    dance_state[1].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
};""",
        "idempotency_check": "[DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),",
    },
]


def apply_patches():
    if not KEYMAP_C.exists():
        print(f"ERROR: {KEYMAP_C} not found", file=sys.stderr)
        return 1

    content = KEYMAP_C.read_text()
    original_content = content
    applied = []
    skipped = []

    for patch in PATCHES:
        # Idempotency check: if the replacement is already in the file, skip
        if "idempotency_check" in patch and patch["idempotency_check"] in content:
            skipped.append(patch["description"])
            continue

        # If the find string doesn't exist, the patch can't apply
        if patch["find"] not in content:
            skipped.append(f"{patch['description']} (find string not found — Oryx may have changed the surrounding code)")
            continue

        content = content.replace(patch["find"], patch["replace"], 1)
        applied.append(patch["description"])

    if content != original_content:
        KEYMAP_C.write_text(content)
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
