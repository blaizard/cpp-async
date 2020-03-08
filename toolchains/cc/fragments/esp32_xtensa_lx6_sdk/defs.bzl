load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def toolchain_fragment_esp32_xtensa_lx6_sdk():
    sdk_package_name = "esp32_xtensa_lx6_sdk_4.0"

    http_archive(
        name = sdk_package_name,
        build_file = "//toolchains/cc/fragments/esp32_xtensa_lx6_sdk:{}.BUILD".format(sdk_package_name),
        urls = [
            "https://github.com/blaizard/bzd-esp32-xtensa-sdk/archive/4.0.zip",
        ],
        strip_prefix = "bzd-esp32-xtensa-sdk-4.0",
        sha256 = "fc2042bbf8a172bf3e36719e4b42d2256a5ff734a56020aab71d73960711d9a2",
    )

    return {
        "builtin_include_directories": [
            "%package(@{}//)%/include".format(sdk_package_name),
        ],
        "system_directories": [
            "external/{}/include".format(sdk_package_name),
        ],
        "compile_flags": [
            "-MMD",
            "-MP",
            "-DCONFIG_IDF_TARGET_ESP32=1",
        ],
        "linker_dirs": [
            "external/{}/ld".format(sdk_package_name),
            "external/{}/lib".format(sdk_package_name),
        ],
        "link_flags": [
            "-nostdlib",
            "-u", "call_user_start_cpu0",
            "-Wl,--start-group",

            # Linker scripts
            "-Tesp32_out.ld",
            # Important, from https://github.com/espressif/esp-idf/blob/master/components/esp32/component.mk
            # ld_include_panic_highint_hdl is added as an undefined symbol because otherwise the
            # linker will ignore panic_highint_hdl.S as it has no other files depending on any
            # symbols in it.
            "-u", "ld_include_panic_highint_hdl",
            "-Tesp32.project.ld",
            "-Tesp32.peripherals.ld",
            "-Tesp32.rom.ld",
            "-Tesp32.rom.libgcc.ld",
            "-Tesp32.rom.syscalls.ld",
            "-Tesp32.rom.newlib-data.ld",
            "-Tesp32.rom.newlib-funcs.ld",

            # Libraries
            "-lapp_trace",
            "-lapp_update",
            "-u", "esp_app_desc",
            "-lasio",
            "-lbootloader_support",
            "-lbt",
            "-lcoap",
            "-lconsole",
            "-lcxx",
            "-u", "__cxa_guard_dummy",
            "-u", "__cxx_fatal_exception",
            "-ldriver",
            "-lefuse",
            "-lesp-tls",
            "-lesp32",
            "-lesp_adc_cal",
            "-lesp_common",
            "-lesp_eth",
            "-lesp_event",
            "-lesp_gdbstub",
            "-lesp_http_client",
            "-lesp_http_server",
            "-lesp_https_ota",
            "-lesp_local_ctrl",
            "-lesp_ringbuf",
            "-lesp_rom",
            "-lesp_websocket_client",
            "-lesp_wifi",
            "-lcore",
            "-lrtc",
            "-lnet80211",
            "-lpp",
            "-lsmartconfig",
            "-lcoexist",
            "-lespnow",
            "-lphy",
            "-lmesh",
            "-lespcoredump",
            "-lexpat",
            "-lfatfs",
            "-lfreemodbus",
            "-lfreertos",
            "-Wl,--undefined=uxTopUsedPriority",
            "-lheap",
            "-lidf_test",
            "-ljsmn",
            "-ljson",
            "-llibsodium",
            "-llog",
            "-llwip",
            "-lmain",
            "-lmbedtls",
            "-lmdns",
            "-lmqtt",
            "-lnewlib",
            "-lc",
            "-lm",
            "-u", "newlib_include_locks_impl",
            "-u", "newlib_include_heap_impl",
            "-u", "newlib_include_syscalls_impl",
            "-lnghttp",
            "-lnvs_flash",
            "-lopenssl",
            "-lprotobuf-c",
            "-lprotocomm",
            "-lpthread",
            "-u", "pthread_include_pthread_impl",
            "-u", "pthread_include_pthread_cond_impl",
            "-u", "pthread_include_pthread_local_storage_impl",
            "-lsdmmc",
            "-lsoc",
            "-lspi_flash",
            "-lspiffs",
            "-ltcp_transport",
            "-ltcpip_adapter",
            "-lulp",
            "-lunity",
            "-lvfs",
            "-lwear_levelling",
            "-lwifi_provisioning",
            "-lwpa_supplicant",
            "-lxtensa",
            "-lhal",
            "-lgcc",
            "-lstdc++",
            "-lgcov",
            #"-Wl,--end-group",
            "-fno-rtti",
        ],
        "filegroup_dependencies": [
            "@{}//:files".format(sdk_package_name),
        ],
    }