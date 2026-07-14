# Custom QMK features in this keymap

## DUAL_FUNC keys (Oryx-style)

The keymap uses custom keycodes `DUAL_FUNC_0` through `DUAL_FUNC_6` that
ZSA's Oryx software generates. Each one is a `#define` that wraps `LT(N, kc)`,
intercepted by `process_record_user()` in `keymap.c` to fire different
keycodes on tap vs hold.

| Define | Tap | Hold |
|---|---|---|
| `DUAL_FUNC_0` | `Z` | `Cmd+Z` (undo) |
| `DUAL_FUNC_1` | `X` | `Cmd+X` (cut) |
| `DUAL_FUNC_2` | `C` | `Cmd+C` (copy) |
| `DUAL_FUNC_3` | `V` | `Cmd+V` (paste) |
| `DUAL_FUNC_4` | Left GUI (Cmd) | Left Alt (Option) |
| `DUAL_FUNC_5` | `-` (minus) | `+` (plus) |
| `DUAL_FUNC_6` | `P` | `"` (double quote) |

## TAP_DANCE (top-left key on base layer)

The first key on row 2 of the base layer uses `DANCE_0`, a tap dance:

| Tap count | Output |
|---|---|
| 1 tap | `~` (tilde) |
| 2 taps | `` ` `` (grave) |
| 3+ taps | extra tildes |

## CAPS_WORD

The `CW_TOGG` key on the base layer (left thumb row) toggles Caps Word
mode. When enabled, letters are shifted until the current word ends.
Useful for typing constants like `API_KEY` without holding Shift.

## AUTOCORRECT

`AC_TOGG` on layer 1 (top-right key) toggles QMK's built-in autocorrect.
When ON, common typos are auto-corrected after you press space or
punctuation:

- `teh ` → `the `
- `recieve ` → `receive `
- `adn ` → `and `
- `hte ` → `the `

The current custom dictionary is generated from
`nvWgW/autocorrect_dict.txt`. It includes QMK's default corrections plus
local test entries like `gglobe -> world` and `childe -> pineapple`.
See `docs/autocorrect.md` for the full flow.

Tapped Oryx dual-function letters are manually fed into Autocorrect so
words containing custom keys like `C`, `F`, `P`, `V`, `X`, and `Z` can
still be corrected.

The firmware forces Autocorrect on at keyboard startup so the persisted
EEPROM toggle state cannot leave it silently disabled after flashing.

Toggle OFF when typing code or terminal commands to avoid false
corrections.

## COMBOS

Two base-layer combos are currently generated from Oryx:

| Combo | Output |
|---|---|
| Left Shift + Backspace | Delete |
| Backspace + Right Ctrl | Ctrl+Shift+Opt+Cmd+Delete |

## RGB matrix

Per-key RGB with custom color schemes for each layer:
- Layer 0 (base): mixed warm/cool with some highlight keys
- Layer 1 (symbol): mostly cool with some warm accents
- Layer 2 (media): mostly teal/cyan

Colors are baked into the firmware via the `ledmap[]` array in
`keymap.c` and the `set_layer_color()` function.

## Layer switching

| Layer | Number | Activate with | Key position |
|---|---|---|---|
| BASE | 0 | (default) | — |
| SYMB | 1 | `TG(1)` (toggle) | top middle row, both halves |
| MDIA | 2 | `TO(2)` (switch) | top middle row, right half |
