#!/bin/bash

set -e

WORKSPACE_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Sanitize
./tools/bazel run //tools/sanitizer:formatter
./tools/bazel run //tools/sanitizer:analyzer

# Generate documentation
rm -rfd "$WORKSPACE_PATH/docs/api"
mkdir "$WORKSPACE_PATH/docs/api" "$WORKSPACE_PATH/docs/api/cc" "$WORKSPACE_PATH/docs/api/bazel"

# To be fixed, the new version of doxygen is built versus a shared lib from clang 9
#./tools/bazel run //tools/documentation/cc -- --output "$WORKSPACE_PATH/docs/api/cc"
./tools/bazel run //tools/documentation/bazel -- "$WORKSPACE_PATH/docs/api/bazel"
