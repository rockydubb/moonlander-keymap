# Moonlander Custom QMK Keymap

This is Rocky's personal Moonlander keymap with custom QMK features on top of the
ZSA Oryx layout. Built using a forked [ZSA blog recipe](https://blog.zsa.io/oryx-custom-qmk-features/).

## Quick start

```bash
# Build only
./build.sh

# Build and open Keymapp for flashing
./build.sh flash
```

The .bin output goes to `zsa_moonlander_reva_nvWgW.bin` in the repo
root. Drag it into [Keymapp](https://www.zsa.io/flash) to flash.

## Documentation

See `docs/` for detailed guides. Start with [`docs/README.md`](docs/README.md) for the index.

## Layout

| Folder | Purpose |
|---|---|
| `nvWgW/` | Your Oryx keymap + custom QMK code. This is the source of truth for your layout. |
| `qmk_firmware/` | ZSA's QMK firmware fork, gitignored. Cloned automatically by `build.sh` and the GitHub Action. |
| `.github/workflows/` | GitHub Action that fetches the latest Oryx layout, merges it with your custom code, and builds the firmware. |
| `build.sh` | One-command local build. |

## How the workflow works

Two pieces work together: **Oryx** (for the graphical layout editor) and
**this repo** (for custom QMK code and the build).

```
┌──────────────────┐    ┌──────────────────┐    ┌──────────────────┐
│  ZSA Oryx Web    │    │  GitHub Action   │    │  Your Macbook    │
│  (edit layout)   │───▶│  (build & ship)  │◀──▶│  (build.sh)      │
└──────────────────┘    └──────────────────┘    └──────────────────┘
        │                       │                       │
        ▼                       ▼                       ▼
   Oryx layout          Firmware .bin            Firmware .bin
   (oryx branch)        (downloadable            (ready to flash
                         artifact)                via Keymapp)
```

### Edit your layout in Oryx

1. Go to https://configure.zsa.io/moonlander
2. Edit keys, layers, lighting
3. Click "Compile this layout"
4. The GitHub Action picks up your changes on next build

### Build locally (fastest for iterating)

```bash
./build.sh
# open the .bin in Keymapp and flash
```

The build script auto-detects the latest ZSA QMK firmware version, clones
`zsa/qmk_firmware` if needed, and compiles.

### Build on GitHub (used by Oryx sync)

```bash
git add .
git commit -m "your message"
git push origin main
```

Then go to the **Actions** tab → **Fetch and build layout** → **Run workflow**.
Download the artifact zip and flash with Keymapp.

The action:
1. Fetches the latest Oryx layout via ZSA's GraphQL API
2. Drops the Oryx files into `nvWgW/` on the `oryx` branch
3. Merges `oryx` → `main` (preserving your custom code)
4. Clones `zsa/qmk_firmware` (matching the Oryx-pinned firmware version)
5. Builds the firmware in a Docker container
6. Uploads the .bin as a downloadable artifact

## Custom QMK features

The keymap in `nvWgW/keymap.c` includes:

- **DUAL_FUNC_* keys** — tap one key for a letter, hold for a different key.
  E.g. tap = `p`, hold = `"`. These are ZSA-Oryx-style custom keycodes that
  are baked into the firmware (not editable in VIA).
- **TAP_DANCE** — the top-left key on the base layer cycles through
  `` ` `` and `~` based on tap count.
- **CAPS_WORD** — `CW_TOGG` on the base layer enables Shift-for-next-word.
- **AUTOCORRECT** — QMK's built-in autocorrect, toggle with `AC_TOGG` on
  layer 1 (top-right key).
- **RGB matrix** — per-key RGB with custom color schemes per layer.
- **Oryx compatibility module** — `zsa/oryx` is loaded so the Oryx-emitted
  keymap layers and CSS color schemes work.

## Adding new QMK features

1. Edit `nvWgW/keymap.c` and/or `nvWgW/rules.mk`
2. Run `./build.sh` to test locally
3. If it works, commit and push to `main`
4. The next GitHub Action run will use your updated code

To enable a new QMK feature, add the corresponding `*_ENABLE = yes` line
to `rules.mk`. Common ones:

| Feature | rules.mk line | Use |
|---|---|---|
| `TAP_DANCE_ENABLE` | (already on) | Multi-tap key behaviors |
| `CAPS_WORD_ENABLE` | (already on) | Caps word |
| `AUTOCORRECT_ENABLE` | (already on) | Autocorrect typos |
| `KEY_OVERRIDE_ENABLE` | `KEY_OVERRIDE_ENABLE = yes` | Override specific key combos |
| `REPEAT_KEY_ENABLE` | `REPEAT_KEY_ENABLE = yes` | `QK_REP` = repeat last key |
| `KEY_LOCK_ENABLE` | `KEY_LOCK_ENABLE = yes` | Hold down next key |
| `LEADER_ENABLE` | `LEADER_ENABLE = yes` | Sequence-trigger macros |
| `DYNAMIC_MACROS_ENABLE` | `DYNAMIC_MACROS_ENABLE = yes` | Record/play macros at runtime |
| `COMBO_ENABLE` | `COMBO_ENABLE = yes` | Multi-key combos |

## Layers

| Layer | Number | Activate with |
|---|---|---|
| BASE | 0 | (default) |
| SYMB | 1 | `TG(1)` — toggle, top middle row |
| MDIA | 2 | `TO(2)` — switch, top middle row (right) |

## Autocorrect notes

Autocorrect is enabled by default at boot. Toggle it on/off with `AC_TOGG`
on layer 1, top-right key (replaced F11).

QMK's default English typo dictionary is baked in. To add a custom word
list (typo → correction pairs), use `qmk generate-autocorrect-data`
with a text file. Note: most tech terms fail QMK's "must not be substring
of a real English word" check, so the default dictionary + the
`AC_TOGG` toggle is usually the most practical approach.

## Files in this repo

```
.
├── README.md                                      # this file
├── build.sh                                       # one-command local build
├── Dockerfile                                     # GitHub Action build env
├── LICENSE.md                                     # ZSA's license
├── .gitignore                                     # excludes qmk_firmware/
├── .github/
│   └── workflows/
│       └── fetch-and-build-layout.yml             # Oryx fetch + build action
├── nvWgW/                                         # your keymap
│   ├── keymap.c                                   # C source
│   ├── config.h                                   # keyboard config
│   ├── keymap.json                                # ZSA marker
│   └── rules.mk                                   # feature flags
└── qmk_firmware/                                  # ZSA QMK source (gitignored)
```

## Troubleshooting

### Build fails with "Module 'zsa/oryx' not found"

The action clones QMK into `qmk_firmware/`, then the build's `make` reads
`nvWgW/keymap.json` which references the `zsa/oryx` module. The `zsa/oryx`
module is bundled inside `zsa/qmk_firmware` under `modules/zsa/`. If you
cloned upstream `qmk/qmk_firmware` instead, the build will fail. Re-run
`./build.sh` — it pulls `zsa/qmk_firmware` automatically.

### `qmk: command not found`

Install: `brew install qmk/qmk/qmk`

### Build complains about flash or device

The Moonlander needs to be in bootloader mode to flash. Hold the top-left
key on the left half while plugging in, OR use Keymapp's "Enter
bootloader" button.

### Layer 1 doesn't show AC_TOGG

Make sure you ran the Oryx sync last (the action's first step pulls
the latest Oryx layout, which would overwrite your `nvWgW/keymap.c`
changes if you edit layer 1 in Oryx). When in doubt, edit `nvWgW/keymap.c`
directly and re-run `./build.sh`.
