# QMK Autocorrect

Autocorrect is enabled for this keymap with:

```make
AUTOCORRECT_ENABLE = yes
```

The firmware forces Autocorrect on during keyboard startup so a stale
EEPROM toggle state cannot silently leave it disabled after flashing.

The toggle key is `AC_TOGG` on layer 1, top-right. Press it only when
you intentionally want to turn Autocorrect off or back on.

## Dictionary behavior

This keymap now uses a custom dictionary file:

```text
nvWgW/autocorrect_dict.txt   # human-editable source
nvWgW/autocorrect_data.h     # generated QMK header
```

The source file starts with QMK's default 70 corrections, then adds local
custom corrections. This keeps the default dictionary behavior while
letting us add our own test words.

QMK's Autocorrect code checks for `autocorrect_data.h`. If one is
present, QMK uses it. If not, QMK automatically falls back to its
built-in default dictionary:

```c
#if __has_include("autocorrect_data.h")
#    include "autocorrect_data.h"
#else
#    include "autocorrect_data_default.h"
#endif
```

When the custom header is absent, the compiler prints this during
`./build.sh qmk`:

```text
Autocorrect is using the default library.
```

With the current custom dictionary, that message should not appear.

Examples preserved from QMK's default dictionary include:

| Typed | Corrected to |
|---|---|
| `recieve` | `receive` |
| `swtich` | `switch` |
| `thresold` | `threshold` |
| `udpate` | `update` |
| `widht` | `width` |

Local test entries:

| Typed | Corrected to |
|---|---|
| `gglobe` | `world` |
| `childe` | `pineapple` |

## Adding more corrections

Edit `nvWgW/autocorrect_dict.txt` and add one correction per line:

```text
typo -> correction
```

`build.sh` regenerates `nvWgW/autocorrect_data.h` automatically before
building, so the normal build and flash commands stay the same.

## Flashing after Autocorrect changes

To build the latest Oryx layout, keep the repo's local QMK patches, and
flash with Zapp:

```bash
./build.sh flash
```

When Zapp waits for the keyboard, press the Moonlander's `QK_BOOT` key
or hardware reset button. Zapp will detect bootloader mode and flash the
built `.bin`.

## Testing

After flashing, open a plain text field and type:

```text
gglobe<space>
childe<space>
widht<space>
thresold<space>
```

They should become:

```text
world<space>
pineapple<space>
width<space>
threshold<space>
```

`gglobe` and `childe` are local test entries that macOS system
autocorrect should ignore, which makes them useful for confirming the
keyboard firmware is doing the correction.

The keymap also feeds tapped Oryx dual-function letters such as `C`,
`F`, `P`, `V`, `X`, and `Z` into Autocorrect manually. Oryx sends those
letters through custom handlers, so without this bridge Autocorrect can
miss words containing those letters.
