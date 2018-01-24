COPTS = [
	"-std=c++11",
	"-g",
	"-Wall",
	"-Wextra",
	"-Werror",
]

cc_library(
  name = "dobbs_logger",
  srcs = [
    "logger.cc",
    "log-impl.h",
  ],
  hdrs = [
    "logger.h",
    "log-impl.h",
  ],
  visibility=[
  	"//visibility:public",
  ],
  copts = COPTS,
)