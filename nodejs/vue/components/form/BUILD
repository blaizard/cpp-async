load("//tools/bazel_build/rules:nodejs.bzl", "bzd_nodejs_library")

bzd_nodejs_library(
    name = "form",
    srcs = glob([
        "**/*.vue",
    ]),
    visibility = ["//visibility:public"],
    deps = [
        "//nodejs:vue",
        "//nodejs/core:upload",
        "//nodejs/core:validation",
        "//nodejs/vue/directives:touch",
    ],
)
