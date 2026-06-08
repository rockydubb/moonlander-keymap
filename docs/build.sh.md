# build.sh

One-command local build for the Moonlander keymap.

## What it does

1. Detects the latest ZSA QMK firmware version (looks for the latest
   `firmware<N>` branch on `zsa/qmk_firmware`).
2. If `qmk_firmware/` doesn't exist, clones `zsa/qmk_firmware` at that
   version and inits its submodules.
3. Copies your `nvWgW/` keymap into the QMK build tree.
4. Runs `qmk compile -kb zsa/moonlander/reva -km nvWgW`.
5. Prints the path to the resulting .bin.

## Usage

```bash
# Build only
./build.sh

# Build + open Keymapp for flashing
./build.sh flash
```

## Output

The compiled firmware is at:
```
qmk_firmware/zsa_moonlander_reva_nvWgW.bin
```

## Why pin a specific ZSA QMK version?

ZSA Oryx produces a `keymap.c` that targets a specific QMK firmware
version. If you build with a newer QMK, the keymap might fail to
compile. The action and the build script both pin to whatever version
Oryx last used (`firmware<N>` branch on zsa/qmk_firmware).

## Requirements

- `qmk` CLI in `$PATH` (`brew install qmk/qmk/qmk`)
- `arm-none-eabi-gcc` (installed automatically by `qmk setup`)
- `git`
- Internet access on first run (to clone zsa/qmk_firmware)

## Updating the ZSA QMK version

Just delete the `qmk_firmware/` directory and re-run `./build.sh`. It
will re-clone at the latest version.
