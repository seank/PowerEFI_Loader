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
    "uart.cc",
    "uart.h",
  ],
  hdrs = [
    "uart.h",
  ],
  visibility=[
    "//visibility:public",
  ],
  copts = COPTS,
)
