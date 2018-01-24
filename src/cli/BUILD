COPTS = [
	"-std=c++11",
	"-g",
	"-Wall",
	"-Wextra",
]

cc_binary(
	name = "sf2_cli_loader",
	srcs = [
		"main.cc",
	],
	copts = COPTS,
	deps= [
	  "//src/lib/logging:dobbs_logger"
	]
)
