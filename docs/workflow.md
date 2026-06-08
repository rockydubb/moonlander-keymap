# Daily workflow — Oryx → local build → flash

The whole point of this repo is to make the Oryx → build → flash cycle
fast and local. No more waiting on GitHub Actions.

## The 3-step flow

### 1. Edit in Oryx

- Go to https://configure.zsa.io/moonlander
- Edit keys, layers, lighting
- Click **"Compile this layout"** at the bottom

That's it. Oryx now has your latest layout version. You don't need to
do anything else in Oryx.

### 2. Build locally

In VS Code, open the `moonlander-keymap` folder. In the terminal:

```bash
./build.sh
```

What this does (in order):
1. Calls ZSA's servers, fetches the latest version of your Oryx layout
2. Drops the new keymap.c into `nvWgW/`, replacing Oryx-generated content
   but keeping your custom QMK code (autocorrect, DUAL_FUNC, RGB, etc.)
3. Clones `zsa/qmk_firmware` at the version Oryx targeted (only on first
   run, or if `qmk_firmware/` was deleted)
4. Compiles with `qmk compile`
5. Drops `zsa_moonlander_reva_nvWgW.bin` in the repo root

Takes 30-90 seconds. Watch the terminal for errors.

### 3. Flash

- Open Keymapp (already installed)
- Drag `zsa_moonlander_reva_nvWgW.bin` from the repo root onto Keymapp
- Click the flash button
- Done — your Moonlander has the new layout

Or use `./build.sh flash` which does steps 2 and 3 (build + open Keymapp).

## Saving your work to GitHub

After you've flashed and tested, commit and push your local changes:

```bash
git add .
git commit -m "your message"
git push origin main
```

⚠️ This will fail if Oryx has made new commits to main since your last
push. See the **Rebase dance** section below.

## The rebase dance (do this every time Oryx syncs to main)

Oryx runs the GitHub Action which merges the latest Oryx layout into the
`main` branch on GitHub. If you've also made local changes (custom
keycode additions, autocorrect toggle, etc.), your local `main` and
GitHub's `main` will diverge. When you `git push`, GitHub will reject
your push because it's not a fast-forward.

**To resolve:**

```bash
# Save your .bin (it's untracked) so it doesn't block the rebase
mv zsa_moonlander_reva_nvWgW.bin /tmp/moonlander-build.bin

# Pull and rebase
git pull --rebase origin main

# Conflicts will appear in nvWgW/config.h and nvWgW/keymap.c
# Take Oryx's versions (they have the latest content):
git checkout --theirs nvWgW/config.h nvWgW/keymap.c

# Re-apply any customizations you made (e.g. AC_TOGG):
# Edit nvWgW/keymap.c — replace KC_F11 with AC_TOGG on layer 1, top-right

# Stage and continue
git add nvWgW/config.h nvWgW/keymap.c
GIT_EDITOR=true git rebase --continue

# Restore the .bin
mv /tmp/moonlander-build.bin zsa_moonlander_reva_nvWgW.bin

# Push
git push origin main
```

The conflicts in `nvWgW/` are normal — Oryx regenerates the keymap
from scratch each time, so any local edits to `keymap.c` are seen as
conflicts.

**Pro tip:** if you want to avoid conflicts, do all your keymap edits
in Oryx (web UI) and reserve local `keymap.c` edits for QMK features
that Oryx can't do (like custom autocorrect dictionaries, custom
keycodes, advanced RGB effects).

## When to run the GitHub Action

You almost never need to. `./build.sh` does the same job locally,
faster, with no upload/download cycle. Use the GitHub Action only if:
- You're away from your Mac and need to build from a browser
- You want to share a build with someone else
- You're debugging a build that fails locally (the action's logs are
  more readable than a long terminal scrollback)

To run the action:
1. Push your local changes to `main` (using the rebase dance above)
2. Go to https://github.com/rockydubb/moonlander-keymap/actions
3. Click **"Fetch and build layout"** → **"Run workflow"** → **"Run workflow"**
4. Wait ~2-3 minutes
5. Download the artifact zip from the bottom of the run page
6. Unzip, drag the .bin to Keymapp
