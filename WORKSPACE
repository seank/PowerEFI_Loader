workspace(name = "PowerEFI_Loader")

new_http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.7.0.zip",
    sha256 = "b58cb7547a28b2c718d1e38aee18a3659c9e3ff52440297e965f5edffe34b6d0",
    build_file = "gtest.BUILD",
)

git_repository(
    name = "google_styleguide",
    remote = "https://github.com/google/styleguide.git",
)

git_repository(
    name = "PowerEFI_SmartFusion_Programmer",
    remote = "https://github.com/seank/PowerEFI_SmartFusion_Programmer.git",
    commit = "a2dd82acfd38cc89fd839ea1852006bdaef4e87f",
)

git_repository(
    name = "google_ahdlc",
    remote = "https://github.com/google/ahdlc.git",
    commit = "4a76442aea022842412a0ce204ccecde1b5d91fd",
)

# proto_library, cc_proto_library, and java_proto_library rules implicitly
# depend on @com_google_protobuf for protoc and proto runtimes.
# This statement defines the @com_google_protobuf repo.
http_archive(
    name = "com_google_protobuf",
    sha256 = "cef7f1b5a7c5fba672bec2a319246e8feba471f04dcebfe362d55930ee7c1c30",
    strip_prefix = "protobuf-3.5.0",
    urls = ["https://github.com/google/protobuf/archive/v3.5.0.zip"],
)
