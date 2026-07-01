# QMK Autocorrect

Autocorrect is enabled for this keymap with:

```make
AUTOCORRECT_ENABLE = yes
```

The toggle key is `AC_TOGG` on layer 1, top-right. Press it to turn
Autocorrect on or off. The state is stored by QMK, so if corrections do
not happen after flashing, press `AC_TOGG` once and test again.

## Dictionary behavior

No custom dictionary file is required for Autocorrect to work.

QMK's Autocorrect code checks for a custom `autocorrect_data.h` file. If
one is present, QMK uses it. If not, QMK automatically falls back to its
built-in default dictionary:

```c
#if __has_include("autocorrect_data.h")
#    include "autocorrect_data.h"
#else
#    include "autocorrect_data_default.h"
#endif
```

The current build uses the default dictionary. The compiler prints this
during `./build.sh qmk`:

```text
Autocorrect is using the default library.
```

Examples from QMK's default dictionary include:

| Typed | Corrected to |
|---|---|
| `recieve` | `receive` |
| `swtich` | `switch` |
| `thresold` | `threshold` |
| `udpate` | `update` |
| `widht` | `width` |

## Custom dictionary later

A custom dictionary is only needed if the default list misses typos you
care about, or if you want personal shorthand, names, or phrases.

The normal flow is:

```bash
qmk generate-autocorrect-data autocorrect_dict.txt -o nvWgW/autocorrect_data.h
```

Once `nvWgW/autocorrect_data.h` exists, QMK should use that file instead
of the default dictionary during the next build.

## Flashing after Autocorrect changes

To build the latest Oryx layout, keep the repo's local QMK patches, and
flash with Zapp:

```bash
./build.sh flash
```

When Zapp waits for the keyboard, press the Moonlander's `QK_BOOT` key
or hardware reset button. Zapp will detect bootloader mode and flash the
built `.bin`.
