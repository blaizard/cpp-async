load("//tools/bazel_build/rules/third_party/python:dependencies.bzl", "bazel_rules_python_load")
load("//tools/bazel_build/rules/third_party/cc:dependencies.bzl", "bazel_rules_cc_load")
load("//tools/bazel_build/rules/third_party/debian:dependencies.bzl", "bazel_rules_debian_load")
load("//tools/bazel_build/rules/third_party/go:dependencies.bzl", "bazel_rules_go_load")
load("//tools/bazel_build/rules/third_party/gazelle:dependencies.bzl", "bazel_rules_gazelle_load")
load("//tools/bazel_build/rules/third_party/skylib:dependencies.bzl", "bazel_rules_skylib_load")
load("//tools/bazel_build/rules/third_party/docker:dependencies.bzl", "bazel_rules_docker_load")

def bazel_rules_load():
    bazel_rules_python_load()
    bazel_rules_cc_load()
    bazel_rules_debian_load()
    bazel_rules_go_load()
    bazel_rules_gazelle_load()
    bazel_rules_skylib_load()
    bazel_rules_docker_load()
