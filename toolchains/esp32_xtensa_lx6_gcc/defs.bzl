load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("//tools/bazel.build/toolchains:defs.bzl", "toolchain_maker", "toolchain_merge")
load("//toolchains/fragments/esptool:defs.bzl", "toolchain_fragment_esptool")

def _load_esp32_xtensa_lx6_gcc_8_2_0(name):
    # Compiler
    clang_package_name = "esp32_xtensa_lx6_gcc_8_2_0"
    http_archive(
        name = clang_package_name,
        build_file = "//toolchains/esp32_xtensa_lx6_gcc:{}.BUILD".format(clang_package_name),
        urls = [
            "https://dl.espressif.com/dl/xtensa-esp32-elf-gcc8_2_0-esp-2019r2-linux-amd64.tar.gz",
        ],
        strip_prefix = "xtensa-esp32-elf",
        sha256 = "e6d47c1dbd8c8cbfe37271e5e2aac53ee88c9e347ae937e22bf0c73f530efbdf",
    )

    # SDK
    sdk_package_name = "esp32_xtensa_lx6_sdk_v4.1_dev_1935_g647cb628a_dirty"
    http_archive(
        name = sdk_package_name,
        build_file = "//toolchains/esp32_xtensa_lx6_gcc:{}.BUILD".format(sdk_package_name),
        urls = [
            "https://github.com/blaizard/bzd-esp32-xtensa-sdk/archive/master.zip",
        ],
        strip_prefix = "bzd-esp32-xtensa-sdk-master",
        sha256 = "fd5f17a1fbf6891a3e48d85a4acf170044c9c4931e5184a7661611f80ae13cb6",
    )

    toolchain_definition = {
        "cpu": "esp32_xtensa_lx6",
        "compiler": "gcc",
        "platforms": [
            "@//tools/bazel.build/platforms:esp32_xtensa_lx6",
        ],
        "exec_compatible_with": [
            "@//tools/bazel.build/platforms/al:linux",
            "@//tools/bazel.build/platforms/isa:xtensa_lx6",
        ],
        "target_compatible_with": [
            "@//tools/bazel.build/platforms/al:linux",
            "@//tools/bazel.build/platforms/isa:xtensa_lx6",
        ],
        "builtin_include_directories": [
            "%package(@{}//)%/xtensa-esp32-elf/include/c++/8.2.0/xtensa-esp32-elf".format(clang_package_name),
            "%package(@{}//)%/xtensa-esp32-elf/include/c++/8.2.0".format(clang_package_name),
            "%package(@{}//)%/xtensa-esp32-elf/include".format(clang_package_name),
            "%package(@{}//)%/lib/gcc/xtensa-esp32-elf/8.2.0/include".format(clang_package_name),
            "%package(@{}//)%/lib/gcc/xtensa-esp32-elf/8.2.0/include-fixed".format(clang_package_name),
        ],
        "system_directories": [
            "external/{}/xtensa-esp32-elf/include/c++/8.2.0/xtensa-esp32-elf".format(clang_package_name),
            "external/{}/xtensa-esp32-elf/include/c++/8.2.0".format(clang_package_name),
            "external/{}/xtensa-esp32-elf/sys-include".format(clang_package_name),
            "external/{}/lib/gcc/xtensa-esp32-elf/8.2.0/include".format(clang_package_name),
            "external/{}/lib/gcc/xtensa-esp32-elf/8.2.0/include-fixed".format(clang_package_name),
        ],
        "linker_dirs": [
            "external/{}/xtensa-esp32-elf/lib".format(clang_package_name),
            "external/{}/ld".format(sdk_package_name),
            "external/{}/lib".format(sdk_package_name),
        ],
        "compile_flags": [
            "-std=c++14",
            "-static",

            # Do not link or re-order inclusion files
            "-nostdinc",
            "-nostdinc++",
            "--no-standard-includes",
            "-nostdlib",

            # Make the compilation deterministic
            "-fstack-protector",
            "-fPIE",
            "-no-canonical-prefixes",

            # Warnings
            "-Wall",
            "-Wno-missing-braces",
            "-Wno-builtin-macro-redefined",

            # Keep stack frames for debugging
            "-fno-omit-frame-pointer",

            # Optimization
            "-O3",

            # Removal of unused code and data at link time
            "-ffunction-sections",
            "-fdata-sections",
            "-mlongcalls",

            # Use linkstamping instead of these
            "-D__DATE__=\"redacted\"",
            "-D__TIMESTAMP__=\"redacted\"",
            "-D__TIME__=\"redacted\"",
        ],
        "link_flags": [
            # Do not link with shared libraries
            "-Wl,-static",

            # Link little-endian objects
            "-Wl,-EL",

            # Garbage collection
            "-Wl,--gc-sections",
        ],
        "static_runtime_libs": [
            "@{}//:static_libraries".format(clang_package_name),
        ],
        "filegroup_dependencies": [
            "@{}//:includes".format(clang_package_name),
            "@{}//:bin".format(clang_package_name),
            "@{}//:files".format(sdk_package_name),
        ],
        "alias": {
            "sdk": "@{}//:sdk".format(sdk_package_name),
        },
        "bin_ar": "external/{}/bin/xtensa-esp32-elf-ar".format(clang_package_name),
        "bin_as": "external/{}/bin/xtensa-esp32-elf-as".format(clang_package_name),
        "bin_cc": "external/{}/bin/xtensa-esp32-elf-gcc".format(clang_package_name),
        "bin_cpp": "external/{}/bin/xtensa-esp32-elf-g++".format(clang_package_name),
        "bin_cov": "external/{}/bin/xtensa-esp32-elf-gcov".format(clang_package_name),
        "bin_objdump": "external/{}/bin/xtensa-esp32-elf-objdump".format(clang_package_name),
        "bin_ld": "external/{}/bin/xtensa-esp32-elf-gcc".format(clang_package_name),
    }

    toolchain_definition = toolchain_merge(toolchain_definition, toolchain_fragment_esptool())

    toolchain_maker(
        name = name,
        implementation = "linux",
        definition = toolchain_definition,
    )

def load_esp32_xtensa_lx6_gcc():
    _load_esp32_xtensa_lx6_gcc_8_2_0(name = "esp32_xtensa_lx6_gcc")
