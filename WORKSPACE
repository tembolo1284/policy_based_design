# https://docs.bazel.build.versions/master/external.html
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Existing gtest dependency
git_repository(
    name = "gtest",
    remote = "https://github.com/google/googletest",
    commit = "40412d85124f7c6f3d88454583c4633e5e10fc8c"
)

local_repository(
    name = "my_lib",
    path = "lib",
)

# ============================================================================
# Python bindings dependencies (NEW)
# ============================================================================

# Python rules
http_archive(
    name = "rules_python",
    sha256 = "9d04041ac92a0985e344235f5d946f71ac543f1b1565f2cdbc9a2aaee8adf55b",
    strip_prefix = "rules_python-0.26.0",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.26.0/rules_python-0.26.0.tar.gz",
)

load("@rules_python//python:repositories.bzl", "py_repositories", "python_register_toolchains")

py_repositories()

python_register_toolchains(
    name = "python3_11",
    python_version = "3.11",
)

# pybind11_bazel
http_archive(
    name = "pybind11_bazel",
    sha256 = "2c466c6f425b3a5f83f9b6f5c0c83a5b1e6f4f8c0f8e1e2f0e5e6e4f3a2b1c0d",
    strip_prefix = "pybind11_bazel-2.11.1",
    urls = ["https://github.com/pybind/pybind11_bazel/archive/refs/tags/v2.11.1.tar.gz"],
)

# pybind11
http_archive(
    name = "pybind11",
    build_file = "@pybind11_bazel//:pybind11.BUILD",
    sha256 = "d475978da0cdc2d43b73f30910786759d593a9d8ee05b1b6846d1eb16c6d2e0c",
    strip_prefix = "pybind11-2.11.1",
    urls = ["https://github.com/pybind/pybind11/archive/refs/tags/v2.11.1.tar.gz"],
)

load("@pybind11_bazel//:python_configure.bzl", "python_configure")

python_configure(name = "local_config_python")
