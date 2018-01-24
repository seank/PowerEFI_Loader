# PowerEFI_Loader
SmartFusion2 Loader

## Building sources
#From base project directory run:
bazel build //src/cli:sf2_cli_loader
#To execute run:
bazel-bin/src/cli/sf2_cli_loader
#To debug run:
bazel build //src/cli:sf2_cli_loader --compilation_mode=dbg -s
gdbtui bazel-bin/bin/main

## Pushing Code For Review
TODO
