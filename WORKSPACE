# https://docs.bazel.build.versions/master/external.html

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "gtest",
    remote = "https://github.com/google/googletest",
    commit = "40412d85124f7c6f3d88454583c4633e5e10fc8c"
)

local_repository(
    name = "my_lib",
    path = "lib",
)