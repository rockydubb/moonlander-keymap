# Moonlander Custom QMK Keymap

Rocky's personal Moonlander keymap with custom QMK features on top of
the ZSA Oryx layout. Built using a forked [ZSA blog recipe](https://blog.zsa.io/oryx-custom-qmk-features/).

## Quick start

The whole workflow is **3 steps**, all from VS Code's terminal:

```bash
# 1. Edit in Oryx (web UI): https://configure.zsa.io/moonlander
#    Click "Compile this layout" when done.

# 2. Build locally:
./build.sh

# 3. Flash from the terminal:
./build.sh flash
#    Zapp waits for you to press QK_BOOT/reset, then flashes automatically.
```

The .bin output goes to `zsa_moonlander_reva_nvWgW.bin` in the repo
root.

**The build script automatically re-applies your custom QMK snippets
(RGB animation, DANCE_1 tap dance, etc.) after Oryx syncs.** You don't
have to remember to do anything special. See
[Custom QMK snippets and the patch system](#custom-qmk-snippets-and-the-patch-system)
below.

## Commands

| Command | What it does | When to use |
|---|---|---|
| `./build.sh` | Fetch latest Oryx layout + build | **Default.** After editing in Oryx. |
| `./build.sh qmk` | Build WITHOUT fetching from Oryx | After editing `nvWgW/keymap.c` directly (custom QMK code) |
| `./build.sh flash` | Fetch Oryx + build + flash with Zapp | One-shot terminal build/flash workflow |
| `./build.sh keymapp` | Fetch Oryx + build + open Keymapp | GUI fallback |
| `./build.sh fetch` | Same as no args (alias) | If you want to be explicit |

The default behavior (fetch Oryx + build) was set up on 2026-06-08
because Rocky's workflow is 95% editing in Oryx and 5% editing
QMK code directly. Use `./build.sh qmk` for the 5% case.

## Layout

| Folder | Purpose |
|---|---|
| `nvWgW/` | Your Oryx keymap + custom QMK code. This is the source of truth for your layout. |
| `qmk_firmware/` | ZSA's QMK firmware fork, gitignored. Cloned automatically by `build.sh` and the GitHub Action. |
| `.github/workflows/` | GitHub Action that fetches the latest Oryx layout, merges it with your custom code, and builds the firmware. |
| `build.sh` | One-command local build. |
| `docs/` | Detailed documentation (workflow, build.sh, GitHub Actions, custom features, etc.) |

## How the workflow works

Three pieces work together: **Oryx** (for the graphical layout editor),
**GitHub** (for syncing Oryx → your repo), and **your Macbook**
(for local builds).

```
┌──────────────────┐    ┌──────────────────┐    ┌──────────────────┐
│  ZSA Oryx Web    │    │  GitHub          │    │  Your Macbook    │
│  (edit layout)   │───▶│  (auto-sync)     │◀──▶│  (./build.sh)    │
└──────────────────┘    └──────────────────┘    └──────────────────┘
        │                       │                       │
        ▼                       ▼                       ▼
   Oryx layout          Firmware .bin            Firmware .bin
   (pushed to            (downloadable            (ready to flash
    oryx branch)         artifact)                via Keymapp)
```

### Edit in Oryx

1. Go to https://configure.zsa.io/moonlander
2. Edit keys, layers, lighting
3. Click "Compile this layout"
4. (Optional) Run the GitHub Action to sync Oryx → `main`:
   https://github.com/rockydubb/moonlander-keymap/actions

### Build locally

`./build.sh` does the whole thing — fetches Oryx (or uses local keymap if
you pass `qmk`), compiles, and drops a .bin in the repo root.

### Flash from the terminal

`./build.sh flash` builds the latest firmware and then runs:

```bash
zapp flash zsa_moonlander_reva_nvWgW.bin
```

Zapp waits until the Moonlander enters bootloader mode. Press your
`QK_BOOT` key or the hardware reset button when the terminal asks. Once
Zapp detects the bootloader, it flashes the built `.bin` automatically.

Install Zapp with:

```bash
brew install zapp
```

`/Applications/kontroll` can inspect/control live Keymapp state, but its
current command surface does not expose a bootloader/reset command, so
the script does not use Kontroll for flashing.

### Build on GitHub

If you're away from your Mac, you can build on GitHub:

1. Push your local changes: `git add . && git commit -m "..." && git push`
2. Go to the **Actions** tab → **"Fetch and build layout"** → **"Run workflow"**
3. Wait ~2-3 minutes
4. Download the artifact zip from the run's page

The action fetches the latest Oryx layout, merges it with your custom
code, and builds the firmware in a Docker container.

## Custom QMK features

The keymap in `nvWgW/keymap.c` includes:

- **DUAL_FUNC_* keys** — tap one key for a letter, hold for a different
  key. E.g. tap = `p`, hold = `"`. These are ZSA-Oryx-style custom
  keycodes that are baked into the firmware (not editable in VIA).
  - `DUAL_FUNC_0` Z / Cmd+Z (undo)
  - `DUAL_FUNC_1` X / Cmd+X (cut)
  - `DUAL_FUNC_2` C / Cmd+C (copy)
  - `DUAL_FUNC_3` V / Cmd+V (paste)
  - `DUAL_FUNC_4` Left Cmd / Left Option
  - `DUAL_FUNC_5` `-` / `+`
  - `DUAL_FUNC_6` `P` / `"`
- **TAP_DANCE** — the top-left key on the base layer cycles through
  `` ` `` and `~` based on tap count (1 tap = `~`, 2 taps = `` ` ``).
- **CAPS_WORD** — `CW_TOGG` on the base layer enables
  Shift-for-next-word.
- **AUTOCORRECT** — QMK's built-in autocorrect, toggle with `AC_TOGG`
  on layer 1 (top-right key, replaced F11).
- **COMBOS** — two Oryx-generated multi-key combos:
  Left Shift + Backspace = Delete, and Backspace + Right Ctrl =
  Ctrl+Shift+Opt+Cmd+Delete.
- **RGB animations** — layer 0 boots into rainbow-sweep animation
  (CYCLE_LEFT_RIGHT). Cycle through other QMK animations with the
  "Switch ANI" / "Animation" key (`RGB_MODE_FORWARD`). Layers 1-3
  show static Oryx colors.
- **Oryx compatibility module** — `zsa/oryx` is loaded so the
  Oryx-emitted keymap layers and CSS color schemes work.

## The Oryx-vs-local-edits gotcha

**This is the single most important thing to understand about this repo.**

When you edit in Oryx and click "Compile this layout", the Oryx server
regenerates `nvWgW/keymap.c` from scratch. Any local edits you made to
that file get overwritten on the next `./build.sh fetch`.

**What survives Oryx regeneration:**
- The `keymaps[]` array (layer definitions) — Oryx owns this
- Most of the file's boilerplate

**What does NOT survive:**
- Custom QMK functions like `keyboard_post_init_user()` (the one
  that forces the RGB animation on boot)
- Any direct edits to `keymaps[]` (which would be conflicts with Oryx)
- Custom keycode definitions you added

**Workflow rules:**

1. For layout changes (key positions, layers, lighting colors): **edit
   in Oryx**, then `./build.sh`. Your changes are safe.
2. For QMK-specific tweaks (RGB effects, custom keycodes, new
   features): **edit `nvWgW/keymap.c` directly**, then
   `./build.sh qmk` (no fetch). Your changes are safe.
3. If you need to do both: do the Oryx edits first, run `./build.sh`,
   flash, test. Then add your QMK edits, run `./build.sh qmk`, flash
   again.

The current state of `nvWgW/keymap.c` after a `./build.sh` is always
"Oryx's latest + my QMK additions if I used `qmk`."

## Custom QMK snippets and the patch system

The "gotcha" above is solved by a small auto-patcher: every time
`./build.sh` runs, it calls `patches/apply_patches.py` after the Oryx
fetch. The patcher re-applies any QMK snippets Oryx wiped out, so your
customizations always survive syncs.

### What gets re-applied

| Patch | What it does |
|---|---|
| RGB animation on boot | Disables the Oryx ledmap[] override, forces CYCLE_LEFT_RIGHT animation on layer 0 |
| Autocorrect toggle key | Keeps layer 1 top-right mapped to `AC_TOGG` |
| Autocorrect feature flag | Keeps `AUTOCORRECT_ENABLE = yes` in `rules.mk` |

The patcher is **idempotent** — running it on a file that already has
the patches does nothing. So you can run `./build.sh` repeatedly
without accumulating duplicate code.

### Verifying the patcher ran

When you run `./build.sh`, you'll see:

```
▶ Fetching latest Oryx layout for nvWgW (moonlander/reva)...
  ...
  Unzipping into nvWgW/...
  Applying custom QMK patches...
Applied 3 patch(es):
  ✓ Force RGB animation on boot (disable Oryx ledmap[] override)
  ✓ Map layer 1 top-right key to AC_TOGG
  ✓ Enable QMK Autocorrect
```

If the patches are already applied, you'll see "No patches needed"
instead. Either way, the build proceeds with your custom code in
place.

### Adding a new snippet to the patch system

1. Edit `patches/apply_patches.py`
2. Add a new entry to the `PATCHES` list:

   ```python
   {
       "description": "My new tap dance on right thumb",
       "find": "KC_RGUI,    KC_RALT,    KC_RGUI,                    KC_RALT,    KC_TAB,         KC_ENT",
       "replace": "KC_RGUI,    KC_RALT,    TD(DANCE_2),                KC_RALT,    KC_TAB,         KC_ENT",
       "idempotency_check": "TD(DANCE_2),                KC_RALT,    KC_TAB,         KC_ENT",
   },
   ```

3. Run `./build.sh` — the new patch will be applied
4. Commit and push

The patcher is dumb (literal string find-and-replace), so make sure
your `find` string is unique enough to not match elsewhere in the
file. If Oryx ever changes the surrounding code, the patch will fail
to apply and you'll see a warning — update the `find` string to
match the new Oryx output and re-run.

## Adding new QMK features

To enable a new QMK feature, add the corresponding `*_ENABLE = yes`
line to `nvWgW/rules.mk`:

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
| App Lay 3 | 3 | (app-specific) |

## Autocorrect notes

Autocorrect is enabled by default at boot. Toggle it on/off with
`AC_TOGG` on layer 1, top-right key (replaced F11).

No custom dictionary file is required for the current setup. QMK uses
its built-in default English typo dictionary when `autocorrect_data.h`
is not present, and the build confirms this with:

```text
Autocorrect is using the default library.
```

To add a custom word list later, use `qmk generate-autocorrect-data`
with a text file. Most tech terms fail QMK's "must not be substring of a
real English word" check, so the default dictionary + the `AC_TOGG`
toggle is usually the most practical approach. See
`docs/autocorrect.md` for the full flow.

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
│   ├── keymap.c                                   # C source (Oryx-emitted + QMK custom)
│   ├── config.h                                   # keyboard config
│   ├── keymap.json                                # ZSA marker
│   └── rules.mk                                   # feature flags
├── patches/                                       # auto-applied QMK snippets (see "patch system")
│   └── apply_patches.py
├── docs/                                          # detailed documentation
└── qmk_firmware/                                  # ZSA QMK source (gitignored)
```

## Documentation

See `docs/` for detailed guides. Start with
[`docs/README.md`](docs/README.md) for the index.

## Troubleshooting

### Oryx changes don't show up on the keyboard

You probably ran `./build.sh qmk` (or no args, depending on the default)
but the local `nvWgW/keymap.c` is stale. Run `./build.sh fetch` to pull
the latest Oryx content, then flash.

### Animations disappeared after an Oryx fetch

Oryx regenerated `keyboard_post_init_user()`. Re-apply the RGB
animation block (see `docs/custom-features.md` for the snippet),
then `./build.sh qmk` to keep your edit.

### Build fails with "Module 'zsa/oryx' not found"

The `zsa/oryx` module is bundled inside `zsa/qmk_firmware` under
`modules/zsa/`. If you cloned upstream `qmk/qmk_firmware` instead, the
build will fail. Re-run `./build.sh` — it pulls `zsa/qmk_firmware`
automatically.

### `qmk: command not found`

Install: `brew install qmk/qmk/qmk`

### Build complains about flash or device

The Moonlander needs to be in bootloader mode to flash. Hold the
top-left key on the left half while plugging in, OR use Keymapp's
"Enter bootloader" button.

### macOS asks to allow an "accessory" after flashing

That's the Moonlander re-enumerating as a USB device after the flash.
Harmless. macOS remembers your choice per USB port, so it'll stop
asking after a few flashes on the same port.
