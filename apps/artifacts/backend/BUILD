load("//tools/bazel_build/rules:nodejs.bzl", "bzd_nodejs_binary")

bzd_nodejs_binary(
    name = "backend",
    srcs = glob([
        "*.mjs",
    ]),
    args = [
        "--static",
        "/tmp/bzd/frontend",
        "--data",
        "/tmp/bzd/db",
    ],
    main = "app.mjs",
    packages = {
        "commander": "",
    },
    visibility = [
        "//apps/artifacts:__pkg__",
    ],
    deps = [
        "//apps/artifacts:api",
        "//apps/artifacts/plugins:backend",
        "//nodejs/core:cache",
        "//nodejs/core:exception",
        "//nodejs/core:filesystem",
        "//nodejs/core:log",
        "//nodejs/core/api:server",
        "//nodejs/core/http:server",
        "//nodejs/db:utils",
        "//nodejs/db/key_value_store:disk",
    ],
)
