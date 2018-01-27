# PowerEFI_Loader

## SmartFusion2 Loader

### Building sources

```bash
# from base project directory run:
bazel build //src/cli:sf2_cli_loader
```

```bash
# to execute run:
bazel-bin/src/cli/sf2_cli_loader
```

```bash
# to debug run:
bazel build //src/cli:sf2_cli_loader --compilation_mode=dbg -s
gdbtui bazel-bin/bin/main
```

### Pushing Code For Review

TODO