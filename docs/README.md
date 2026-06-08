# docs/ — Documentation index

| File | What it covers |
|---|---|
| `README.md` (top-level) | What this repo is, quick start, full feature list, troubleshooting |
| `workflow.md` | The 3-step daily flow: Oryx → `./build.sh` → Keymapp. The Oryx-vs-local-edits gotcha. The rebase dance for pushing after Oryx syncs. |
| `build.sh.md` | What `build.sh` does, the 3 commands, why fetch is the default, troubleshooting |
| `github-actions-explained.md` | What GitHub Actions is in plain English |
| `custom-features.md` | All 7 DUAL_FUNC keys, tap dance, caps word, autocorrect, RGB, layers — what each does |
| `keymap-folder.md` | What's in `nvWgW/`, when to edit what, how to add a new custom keycode |
| `patch-system.md` | The auto-patcher that re-applies custom QMK snippets after Oryx syncs |
| `git-troubleshooting.md` | Common git problems: rebase conflicts, merge conflicts, recovering from mistakes |
| `changelog.md` | What changed in the repo over time |

## Reading order if you're new

1. `README.md` (top-level) — start here
2. `workflow.md` — the daily flow
3. `build.sh.md` — the script you'll run all the time
4. `custom-features.md` — what your keymap actually does
5. `github-actions-explained.md` — what the action is doing in case you ever need to debug it

## The single most important thing to read

If you only read one section of the docs, read **"The Oryx-vs-local-edits gotcha"** in `README.md` (or the more detailed version in `workflow.md`). It explains why some edits get overwritten and how to avoid losing work.
