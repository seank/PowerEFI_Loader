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

Gerrithub is a central location used for easy managment of the code review process. To get an idea of how this is typically done, watch the following video and pay special attention to the 2:25+ mark:

[![Video](http://img.youtube.com/vi/jeWTvDad6VM/0.jpg)](http://www.youtube.com/watch?v=jeWTvDad6VM)

Simply perform your changes and [submit for review](https://review.gerrithub.io/Documentation/intro-project-owner.html#code-review):

```bash
git push ssh://seank@gerrithub.io:29418/seank/PowerEFI_Loader HEAD:refs/for/master
```