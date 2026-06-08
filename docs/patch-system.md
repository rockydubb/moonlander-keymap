# The patch system

## What it is

`patches/apply_patches.py` is a small Python script that re-applies
custom QMK snippets to `nvWgW/keymap.c` after Oryx's regeneration has
wiped them out. It's called automatically by `build.sh` after every
Oryx fetch.

## Why it exists

When you edit in Oryx, the Oryx server regenerates `nvWgW/keymap.c`
from scratch. This wipes out:
- Custom functions like `keyboard_post_init_user()` (the one that
  forces RGB animation on boot)
- Custom tap dance code (DANCE_1, DANCE_2, etc.)
- Any direct edits to the thumb cluster keys
- Anything else QMK-specific that Oryx doesn't know about

Before the patch system, you had to manually re-apply these after
every Oryx sync. Now the script does it for you.

## How it works

Each patch in the `PATCHES` list is a tuple of:
- `description` — human-readable name, printed when applied
- `find` — exact text to search for in `keymap.c`
- `replace` — what to substitute in
- `idempotency_check` — text to check for; if already present, skip the patch

The script:
1. Reads `nvWgW/keymap.c`
2. For each patch, checks if `idempotency_check` is already in the file
3. If not, finds `find` and replaces it with `replace`
4. Writes the file back (only if any patch was applied)

## Currently applied patches

| Patch | What it does |
|---|---|
| RGB animation on boot | Forces `rgb_matrix_mode_noeeprom(6)` in `keyboard_post_init_user()` |
| DANCE_1 to enum | Adds `DANCE_1` to the `tap_dance_codes` enum |
| Left thumb 3rd button | Wires the key to `TD(DANCE_1)` |
| dance_state array | Sizes the array to hold state for 2 dances |
| DANCE_1 function bodies | Registers the on_finished/on_reset functions |

## Adding a new patch

1. Edit `patches/apply_patches.py`
2. Add a new entry to the `PATCHES` list, e.g.:

   ```python
   {
       "description": "My new tap dance on right thumb",
       "find": "KC_RGUI,    KC_RALT,    KC_RGUI,                    KC_RALT,    KC_TAB,         KC_ENT",
       "replace": "KC_RGUI,    KC_RALT,    TD(DANCE_2),                KC_RALT,    KC_TAB,         KC_ENT",
       "idempotency_check": "TD(DANCE_2),                KC_RALT,    KC_TAB,         KC_ENT",
   },
   ```

3. Run `./build.sh` to apply + build + flash
4. Commit and push

## When patches fail to apply

If the find string isn't in the file, the patch is silently skipped
and you get a warning like:

```
Skipped 1 patch(es):
  - My new tap dance on right thumb (find string not found — Oryx may have changed the surrounding code)
```

This means Oryx regenerated the keymap with slightly different code
around the patch anchor. Fix by:
1. Looking at the Oryx-emitted `nvWgW/keymap.c` to see what changed
2. Updating the `find` string to match
3. Re-running `./build.sh`

The patcher is dumb (literal string find-and-replace), so `find`
strings need to match exactly — including whitespace and indentation.

## Limitations

- **Doesn't handle multi-line context changes well.** If Oryx
  completely rewrites a function, the find string might not match
  and the patch silently fails.
- **No conflict resolution.** If two patches want to replace the
  same line, the first one wins and the second one might break
  silently.
- **No rollback.** If a patch makes a mistake, you have to manually
  fix the file or revert via git.

For most cases, the patcher just works. The only time it breaks is
when ZSA releases a major Oryx update that changes the keymap format,
which is rare.
