COPTS = [
	"-std=c++11",
	"-g",
	"-Wall",
	"-Wextra",
	"-Werror",
]

cc_library(
  name = "sf2_isp",
  srcs = [
    "sf2_isp.cc",
    "sf2_isp.h",
  ],
  hdrs = [
    "sf2_isp.h",
  ],
  visibility=[
    "//visibility:public",
  ],
  deps= [
		"//src/lib/logging:dobbs_logger",
		"//src/lib/uart:uart_interface",
  ],
  copts = COPTS,
)
