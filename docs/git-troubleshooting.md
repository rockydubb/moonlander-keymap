# Git troubleshooting

Common problems and how to fix them. Most of these come from the
Oryx + local-edits conflict pattern.

## "Updates were rejected because the remote contains work that you do not have locally"

**Cause:** Oryx synced new commits to `main` on GitHub, but your local
`main` doesn't have them yet. Git refuses to fast-forward.

**Fix:** rebase your local commits on top of GitHub's:

```bash
# Move untracked .bin out of the way
mv zsa_moonlander_reva_nvWgW.bin /tmp/moonlander-build.bin

git pull --rebase origin main

# If there are conflicts, see "Merge conflict in nvWgW/keymap.c" below

GIT_EDITOR=true git rebase --continue
mv /tmp/moonlander-build.bin zsa_moonlander_reva_nvWgW.bin

git push origin main
```

## "Merge conflict in nvWgW/config.h" or "nvWgW/keymap.c"

**Cause:** Oryx regenerated the keymap from scratch. Your local edits
to those files (AC_TOGG, custom DUAL_FUNC, etc.) are seen as conflicts.

**Fix:** take Oryx's version of the conflict, then re-apply your
customizations on top.

```bash
# Take Oryx's version
git checkout --theirs nvWgW/config.h nvWgW/keymap.c

# Re-apply your customizations:
# 1. AC_TOGG on layer 1, top-right key:
#    Find:    KC_F10,         KC_F11,
#    Replace: KC_F10,         AC_TOGG,
#
# 2. Any other DUAL_FUNC_ customizations
# 3. Any other keymap.c changes you made

git add nvWgW/config.h nvWgW/keymap.c
GIT_EDITOR=true git rebase --continue
```

## "Your local changes would be overwritten by checkout"

**Cause:** You have unstaged or uncommitted changes that conflict with
something you're trying to do (pull, checkout, rebase).

**Fix:** stash or commit them first:

```bash
# See what's unstaged
git status

# Option 1: commit them
git add .
git commit -m "WIP: saving in-progress work"

# Option 2: stash them (they go in a safe place, you can restore later)
git stash
# ... do your pull/rebase/checkout ...
git stash pop
```

## "Please commit your changes or stash them before you merge"

**Fix:** same as above. Stash or commit, then continue.

## "fatal: not a git repository"

**Cause:** You're in the wrong directory. The git commands only work
inside the `moonlander-keymap` repo.

**Fix:** `cd` into the repo:

```bash
cd ~/code/Repos/moonlander-keymap
```

## "Permission denied (publickey)" when pushing

**Cause:** GitHub can't authenticate you. Usually means your SSH key
isn't set up, or you're pushing to the wrong remote URL.

**Fix:** check your remote URL:

```bash
git remote -v
# Should show: https://github.com/rockydubb/moonlander-keymap.git
# or: git@github.com:rockydubb/moonlander-keymap.git
```

If using HTTPS, you may need a [Personal Access Token](https://github.com/settings/tokens)
instead of your password (GitHub disabled password auth in 2021).

If using SSH, set up your SSH key: `ssh-add ~/.ssh/id_ed25519`

## "qmk: command not found"

**Cause:** QMK CLI not in `$PATH`.

**Fix:** `brew install qmk/qmk/qmk`

## Build fails with "Module 'zsa/oryx' not found"

**Cause:** QMK was built against the wrong source. Either you used
`~/qmk_firmware` (generic QMK) instead of `zsa/qmk_firmware` (ZSA's
fork), or the `zsa/oryx` module isn't being loaded.

**Fix:** delete `qmk_firmware/` and re-run `./build.sh`. It will
re-clone `zsa/qmk_firmware` automatically.

## "Cannot index object with number" when running build.sh

**Cause:** jq parsing error on the Oryx GraphQL response. Usually means
the layout ID is wrong, or the response structure changed.

**Fix:** check your `ORYX_LAYOUT_ID` env var or the default in
`build.sh` (default: `nvWgW`). The layout ID is in the URL of your
Oryx layout:
https://configure.zsa.io/moonlander/layouts/**YOUR_ID**/latest

## Recovering from a messed-up rebase

If you got into a bad state during a rebase and want to bail:

```bash
git rebase --abort
```

This puts you back to where you were before the rebase started. Safe to
run anytime. Your uncommitted changes in the working tree are preserved.

If you committed something you want to undo:

```bash
# Undo the last commit, keep changes staged
git reset --soft HEAD~1

# Undo the last commit, keep changes unstaged
git reset HEAD~1

# Undo the last commit, throw away changes (DANGEROUS)
git reset --hard HEAD~1
```

## When in doubt

- `git status` shows you what's going on (staged, unstaged, untracked, conflicts)
- `git log --oneline -10` shows recent commits
- `git diff` shows what changed in unstaged files
- `git diff --staged` shows what changed in staged files
- Google the error message — git errors are well-documented
