load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("//tools/bazel_build/toolchains/cc:defs.bzl", "toolchain_maker")
load("//toolchains/cc:defs.bzl", "COPTS_CLANG", "LINKOPTS_CLANG")

def _load_linux_x86_64_clang_9_0_0(name):
    # Load dependencies
    package_name = "linux_x86_64_clang_9_0_0"
    http_archive(
        name = package_name,
        build_file = "//toolchains/cc/linux_x86_64_clang:{}.BUILD".format(package_name),
        urls = [
            "http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz",
        ],
        strip_prefix = "clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04",
        sha256 = "a23b082b30c128c9831dbdd96edad26b43f56624d0ad0ea9edec506f5385038d",
    )

    toolchain_definition = {
        "cpu": "linux_x86_64",
        "compiler": "clang",
        "host_platforms": [
            "@//tools/bazel_build/platforms:linux_x86_64",
        ],
        "exec_compatible_with": [
            "@//tools/bazel_build/platforms/al:linux",
            "@//tools/bazel_build/platforms/isa:x86_64",
        ],
        "platforms": [
            "@//tools/bazel_build/platforms:linux_x86_64",
        ],
        "target_compatible_with": [
            "@//tools/bazel_build/platforms/al:linux",
            "@//tools/bazel_build/platforms/isa:x86_64",
        ],
        "builtin_include_directories": [
            "/usr/include/x86_64-linux-gnu",
            "/usr/include",
            "include/c++/v1".format(package_name),
            "lib/clang/9.0.0/include".format(package_name),
        ],
        "system_directories": [
            "/usr/include/x86_64-linux-gnu",
            "/usr/include",
            "external/{}/include/c++/v1".format(package_name),
            "external/{}/lib/clang/9.0.0/include".format(package_name),
        ],
        "linker_dirs": [
            "external/{}/lib".format(package_name),
        ],
        "compile_flags": [
            "-std=c++17",
            # Add debug symbols, will be removed at the postprocessing stage
            "-g",

            # Do not link or re-order inclusion files
            "-nostdinc++",
            #"-nostdinc",
            "--no-standard-includes",

            # Make the compilation deterministic
            "-fstack-protector",
            "-fPIE",
            "-no-canonical-prefixes",

            # Warnings
            "-Wall",
            "-Wno-missing-braces",
            "-Wno-builtin-macro-redefined",
            "-Wno-unused-command-line-argument",

            # Keep stack frames for debugging
            "-fno-omit-frame-pointer",

            # Optimization
            "-O3",

            # Removal of unused code and data at link time
            "-ffunction-sections",
            "-fdata-sections",

            # Use linkstamping instead of these
            "-D__DATE__=\"redacted\"",
            "-D__TIMESTAMP__=\"redacted\"",
            "-D__TIME__=\"redacted\"",
        ] + COPTS_CLANG,
        "link_flags": LINKOPTS_CLANG + [
            "-fuse-ld=lld",
            "-Wl,--disable-new-dtags",
            "-Wl,--gc-sections",
            "-rdynamic",
            "-stdlib=libc++",
            "-lm",
            "-lc++",
            "-lc++abi",
            "-lc",
            "-lgcc_s",
            "-lgcc",
            "-Wl,-z,relro,-z,now",
            "-no-canonical-prefixes",
            "-Wl,-rpath=%{{absolute_external}}/{}/lib".format(package_name),

            # Stamp the binary with a unique identifier
            "-Wl,--build-id=md5",
            "-Wl,--hash-style=gnu",
        ],
        "coverage_compile_flags": [
            "-fprofile-instr-generate",
            "-fcoverage-mapping",
            "-fprofile-arcs",
            "-ftest-coverage",
            "-fno-inline",
            "-O0",
        ],
        "coverage_link_flags": [
            "-fprofile-instr-generate",
            "-fcoverage-mapping",
            "-fprofile-arcs",
        ],
        "dynamic_runtime_libs": [
            "@{}//:dynamic_libraries".format(package_name),
        ],
        "static_runtime_libs": [
            "@{}//:static_libraries".format(package_name),
        ],
        "filegroup_dependencies": [
            "@{}//:includes".format(package_name),
            "@{}//:bin".format(package_name),
        ],
        "bin_ar": "external/{}/bin/llvm-ar".format(package_name),
        "bin_as": "external/{}/bin/llvm-as".format(package_name),
        "bin_cc": "external/{}/bin/clang".format(package_name),
        "bin_cpp": "external/{}/bin/clang".format(package_name),
        "bin_cov": "external/{}/bin/llvm-cov".format(package_name),
        "bin_objdump": "external/{}/bin/llvm-objdump".format(package_name),
        "bin_ld": "external/{}/bin/clang++".format(package_name),
        "bin_strip": "external/{}/bin/llvm-strip".format(package_name),
    }

    toolchain_maker(
        name = name,
        implementation = "linux",
        definition = toolchain_definition,
    )

def load_linux_x86_64_clang():
    _load_linux_x86_64_clang_9_0_0(name = "linux_x86_64_clang")
