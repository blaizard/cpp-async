load("//tools/bazel_build/rules:nodejs.bzl", "bzd_nodejs_library")

bzd_nodejs_library(
    name = "authentication",
    srcs = [
        "authentication.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":exception",
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "log",
    srcs = [
        "log.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":format",
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "exception",
    srcs = [
        "exception.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":format",
        ":log",
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "event",
    srcs = [
        "event.mjs",
    ],
    visibility = ["//visibility:public"],
)

bzd_nodejs_library(
    name = "format",
    srcs = [
        "format.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "cache",
    srcs = [
        "cache.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":event",
        ":exception",
        ":log",
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "crypto",
    srcs = glob([
        "crypto.mjs",
        "impl/crypto/*",
    ]),
    visibility = ["//visibility:public"],
    deps = [
        ":exception",
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "filesystem",
    srcs = [
        "filesystem.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "localstorage",
    srcs = [
        "localstorage.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "mutex",
    srcs = [
        "mutex.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "router",
    srcs = [
        "router.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":exception",
        "//nodejs:bzd",
        "//nodejs/utils:regexpr",
    ],
)

bzd_nodejs_library(
    name = "stream",
    srcs = [
        "stream.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "template",
    srcs = [
        "template.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":exception",
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "timeseries",
    srcs = [
        "timeseries.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":exception",
        ":log",
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "upload",
    srcs = [
        "upload.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//nodejs:bzd",
    ],
)

bzd_nodejs_library(
    name = "validation",
    srcs = [
        "validation.mjs",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":exception",
        ":format",
        "//nodejs:bzd",
    ],
)
