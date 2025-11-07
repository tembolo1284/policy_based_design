load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")

pybind_extension(
    name = "calculator_py",
    srcs = ["bindings.cpp"],
    deps = ["//lib:Calculator"],
)

py_library(
    name = "calculator",
    srcs = ["__init__.py"],
    data = [":calculator_py"],
    visibility = ["//visibility:public"],
)

py_binary(
    name = "example",
    srcs = ["example.py"],
    deps = [":calculator"],
)
