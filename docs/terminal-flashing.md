# Terminal flashing with Zapp

This repo can build and flash the Moonlander from the terminal:

```bash
./build.sh flash
```

That command does the normal local workflow first:

1. Fetches the latest Oryx layout.
2. Applies the local QMK patches.
3. Builds `zsa_moonlander_reva_nvWgW.bin`.
4. Runs `zapp flash zsa_moonlander_reva_nvWgW.bin`.

## Install Zapp

```bash
brew install zapp
```

Check it with:

```bash
zapp --version
```

## Why not `zapp update`?

`zapp update` is useful for a standard Oryx-only keyboard firmware. It
reads the layout and revision already stored on the keyboard, checks
Oryx for a newer revision, downloads it, and flashes it.

That bypasses this repo's custom build flow. It does not run
`patches/apply_patches.py`, does not compile the local patched keymap,
and can miss custom QMK changes. For this repo, use `zapp flash` with
the local `.bin` that `build.sh` just produced.

## Bootloader handoff

Zapp loads the firmware file, then waits for the keyboard to enter
bootloader mode. When the terminal says it is waiting, press the
Moonlander's `QK_BOOT` key or the hardware reset button.

Your current keymap has `QK_BOOT` on layer 2, top-right key. If that
ever moves in Oryx, the terminal flashing flow still works as long as
there is some way to put the keyboard in bootloader mode.

## Why Kontroll is not used

`/Applications/kontroll` can talk to Keymapp's API for live keyboard
state, layer changes, RGB, status LEDs, and brightness. Its current
command list does not expose a bootloader/reset command, so the script
does not use Kontroll to enter firmware mode.

The reliable automation boundary is:

```text
build.sh builds firmware -> zapp waits -> you press QK_BOOT/reset -> zapp flashes
```

## GUI fallback

To build and open Keymapp instead of using Zapp:

```bash
./build.sh keymapp
```
