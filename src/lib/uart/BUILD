COPTS = [
	"-std=c++11",
	"-g",
	"-Wall",
	"-Wextra",
	"-Werror",
]

cc_library(
  name = "uart_interface",
  srcs = [
    "uart_interface.cc",
    "uart_interface.h",
  ],
  hdrs = [
    "uart_interface.h",
  ],
  visibility=[
    "//visibility:public",
  ],
  deps= [
	  "//src/lib/logging:dobbs_logger"
	],
  copts = COPTS,
)
