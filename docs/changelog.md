# Changelog

What changed in the repo, in reverse chronological order.

## 2026-07-01

### Caps Word, combos, and Autocorrect

Synced the latest Oryx layout after Caps Word was added to the base
layer, left side bottom row second key. The Oryx-generated source also
enabled two combos:

- Left Shift + Backspace -> Delete
- Backspace + Right Ctrl -> Ctrl+Shift+Opt+Cmd+Delete

Enabled QMK Autocorrect in the repo's durable patch flow:

- `AUTOCORRECT_ENABLE = yes` in `nvWgW/rules.mk`
- `AC_TOGG` on layer 1, top-right key
- `patches/apply_patches.py` now reapplies the feature flag and toggle
  key after future Oryx fetches

Verified with `./build.sh qmk`; the build compiled
`process_autocorrect.c`, `process_caps_word.c`, and `process_combo.c`.

### Terminal flashing with Zapp

Changed `./build.sh flash` from "build and open Keymapp" to "build and
flash with Zapp." The script now checks for `zapp`, prints clear
bootloader instructions, and runs:

```bash
zapp flash zsa_moonlander_reva_nvWgW.bin
```

Zapp waits while the user presses `QK_BOOT` or the hardware reset
button, then flashes automatically once the Moonlander appears in
bootloader mode.

Added `./build.sh keymapp` as a GUI fallback that preserves the old
Keymapp handoff behavior.

Added `docs/terminal-flashing.md` and updated the README, workflow docs,
and build script docs to describe the Zapp flow and the current Kontroll
limitation: Kontroll can inspect/control Keymapp live state, but does
not expose a bootloader/reset command.

## 2026-06-08

### Auto-patch system for Oryx-vs-local-edits survival

Added `patches/apply_patches.py` and wired it into `build.sh` to run
after every Oryx fetch. The patcher re-applies any custom QMK snippets
that Oryx's regeneration wiped out, so your customizations survive
syncs automatically.

Currently 5 patches:
- RGB animation on boot (`keyboard_post_init_user()`)
- DANCE_1 to `tap_dance_codes` enum
- Left thumb 3rd button wired to `TD(DANCE_1)`
- `dance_state` array sized to 2
- DANCE_1 function bodies and tap_dance_actions entry

The patcher is idempotent — re-running it does nothing if the patches
are already in place. New snippets can be added by appending to the
`PATCHES` list in `apply_patches.py`.

**Workflow is now fully self-sustaining:** edit in Oryx → run
`./build.sh` → flash. No need to manually re-apply snippets.

### Made "fetch Oryx" the default build behavior

The default for `./build.sh` (no args) is now "fetch latest Oryx
layout + build", because Rocky's workflow is 95% editing in Oryx.
Added `./build.sh qmk` for the 5% case where you've edited QMK code
directly in `nvWgW/keymap.c` and don't want Oryx to overwrite it.

Earlier in the day the default was "build only", which caused confusion
when Oryx changes didn't show up on the keyboard.

### Force RGB animation on boot

The Oryx keymap's `ledmap[]` static colors were clobbering QMK
animation effects on every matrix scan, making the "Switch ANI" /
"Animation" key invisible. Fixed by adding to
`keyboard_post_init_user()` in `nvWgW/keymap.c`:

```c
keyboard_config.disable_layer_led = true;
eeconfig_update_kb(keyboard_config.raw);
rgb_matrix_enable_noeeprom();
rgb_matrix_mode_noeeprom(6);  // CYCLE_LEFT_RIGHT (rainbow sweep)
```

This disables the Oryx layer-LED override system and forces the
keyboard to boot into the CYCLE_LEFT_RIGHT animation. The
`RGB_MODE_FORWARD` key now visibly cycles through all QMK animation
effects. Confirmed working on real hardware.

### Major README + docs rewrite

- Top-level README.md: full rewrite for accuracy. Adds the "Oryx-vs-
  local-edits gotcha" section, the macOS USB accessory prompt
  explanation, the 3 build.sh commands table.
- docs/workflow.md: rewritten to reflect fetch-as-default, expanded
  the rebase dance with the new "re-apply customizations" step.
- docs/build.sh.md: rewritten for the 3-command setup.
- docs/README.md: index updated.

## 2026-06-07

### Major refactor: local-first workflow

Replaced the GitHub Action round-trip with a local `build.sh` script.
You can now edit in Oryx, run one command, and flash — all without
waiting on GitHub Actions.

- **Added** `build.sh` — one-command local build. Fetches latest
  Oryx layout, clones ZSA QMK source if needed, compiles, drops .bin
  in repo root. Pass `flash` to also open Keymapp.
- **Added** `docs/` folder with explanations of build.sh, GitHub
  Actions, keymap folder, custom features, workflow, and git
  troubleshooting.
- **Added** `AC_TOGG` (autocorrect on/off toggle) to layer 1, top-right
  key (replaced F11). Default English autocorrect dictionary is in.
- **Removed** `qmk_firmware/` as a git submodule. Now cloned by
  `build.sh` and the GitHub Action. `.gitignore` excludes it.
- **Updated** `.github/workflows/fetch-and-build-layout.yml` to clone
  `zsa/qmk_firmware` directly instead of using a submodule.

### Verified

`./build.sh` runs end-to-end on macOS. Output: 66 KB
`zsa_moonlander_reva_nvWgW.bin` at repo root, ready to flash via
Keymapp.

## Earlier (in commit history)

- 7 DUAL_FUNC custom keycodes (P-tap/`"`-hold, `-`tap/`+`-hold,
  Z/X/C/V mod-tap, etc.) — generated by Oryx, baked into firmware
- TAP_DANCE on top-left key (toggles `~` and `` ` ``)
- CAPS_WORD via `CW_TOGG` on left thumb
- RGB matrix per-layer colors
- Original GitHub Action (now superseded by `build.sh`)
