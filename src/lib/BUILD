COPTS = [
	"-std=c++11",
	"-g",
	"-Wall",
	"-Wextra",
]

cc_binary(
	name = "sf2_cli_loader",
	srcs = [
		"src/cli/main.cc",
	],
	copts = COPTS,
	deps= [
	  ":dobbs_logger"
	]
)

