COPTS = [
	"-std=c++11",
	"-g",
	"-Wall",
	"-Wextra",
	"-Werror",
]

cc_binary(
	name = "sf2_cli_loader",
	srcs = [
		"main.cc",
	],
	copts = COPTS,
	deps= [
		"//src/lib/logging:dobbs_logger",
		"//src/lib/uart:uart_interface",
		"//src/lib/sf2_isp:sf2_isp",
	],
)
