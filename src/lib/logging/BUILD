COPTS = [
	"-std=c++11",
	"-g",
	"-Wall",
	"-Wextra",
]

cc_library(
  name = "dobbs_logger",
  hdrs = [
    "logger.cc",
    "logger.h",
    "log-impl.h",
  ],
  visibility=[
  	"//src/cli:__pkg__",
  ],
  copts = COPTS,
)