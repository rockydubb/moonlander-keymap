# GitHub Actions — Plain English

GitHub Actions is a free computer that GitHub lends you. You describe
what you want it to do in a YAML file, and GitHub runs those commands
when you tell it to.

## How it works in this repo

The action is defined in `.github/workflows/fetch-and-build-layout.yml`.
It runs the same 7 steps every time you click "Run workflow" on the
Actions tab:

### Step 1: Checkout
Downloads a copy of your repo to GitHub's computer, on a branch called
`oryx`.

### Step 2: Download Oryx source
Calls ZSA's servers and asks for the latest version of your layout.
ZSA replies with a zip file containing the `keymap.c` your Oryx edits
generated.

### Step 3: Unzip and commit
Drops the Oryx zip contents into the `nvWgW/` folder of your repo and
saves them to the `oryx` branch.

### Step 4: Merge Oryx → main
Takes the `oryx` branch (with Oryx's fresh layout) and merges it into
the `main` branch (where your custom QMK code lives). This is how your
custom code (DUAL_FUNC, autocorrect, RGB, etc.) survives the merge.

### Step 5: Clone ZSA QMK firmware
Downloads `zsa/qmk_firmware` from GitHub. The ZSA fork is different
from the generic QMK fork — it has the custom Moonlander source code
(per-key RGB, custom keyboard drivers, the `zsa/oryx` module). We
clone the specific version of QMK that Oryx targeted, so the
compile succeeds.

### Step 6: Build
Runs the firmware compile inside a Docker container. This is the
2-3 minute part. Compiles your keymap into a `.bin` file.

### Step 7: Upload artifact
Bundles the `.bin` into a downloadable zip and shows it on the
Actions run page.

## When does the action run?

Only when you click "Run workflow" on the Actions tab. It does NOT
run on every `git push` — that would be wasteful. You push to `main`,
then go to Actions and click Run to build.

## What are branches?

A branch is a separate version of your code. The Oryx sync only
modifies the `oryx` branch. Your custom code lives on `main`.
The action merges them. You only ever edit `main` directly.

## What is `qmk/qmk_firmware` vs `zsa/qmk_firmware`?

- `qmk/qmk_firmware` = the generic QMK project. Most keyboards use this.
- `zsa/qmk_firmware` = ZSA's fork with Moonlander-specific patches.
  Required for building Moonlander firmware.

## What is the "Actions" tab?

In GitHub, click the **Actions** tab at the top of your repo to see
a list of past runs. Each run shows its steps and a green check or
red X for each one. Click any run to see the full log.

## Why use GitHub Actions instead of building locally?

- You don't need to install QMK toolchain on your Mac (saves disk space)
- Builds run on GitHub's fast hardware (~2-3 min)
- The .bin is downloadable from any browser, any device
- Build history is preserved (you can re-download any past build)

For day-to-day iteration, `build.sh` on your Mac is faster (~30-90s)
and doesn't require pushing to GitHub.
