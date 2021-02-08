{
    "targets": [
        {
            "target_name": "web-rsync",
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": [
                "-fno-exceptions",
            ],
            "cflags_cc": ["-std=c++17"],
            "sources": [
                "./src/index.cpp",
                "<!@(ls -1 ./src/*.cpp)",
                "<!@(ls -1 ./src/**/*.cpp)",
            ],
            "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include_dir\")"],
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"],
            "conditions": [
                [
                    'OS=="mac"',
                    {
                        "xcode_settings": {
                            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                            "CLANG_CXX_LANGUAGE_STANDARD": "gnu++17",
                            "CLANG_CXX_LIBRARY": "libc++",
                            "MACOSX_DEPLOYMENT_TARGET": "10.15",
                        },
                    },
                ],
                [
                    'node_shared_openssl=="false"',
                    {
                        # so when "node_shared_openssl" is "false", then OpenSSL has been
                        # bundled into the node executable. So we need to include the same
                        # header files that were used when building node.
                        "include_dirs": [
                            "<(node_root_dir)/deps/openssl/openssl/include"
                        ],
                        "conditions": [
                            [
                                "target_arch=='ia32'",
                                {
                                    "include_dirs": [
                                        "<(node_root_dir)/deps/openssl/config/piii"
                                    ]
                                },
                            ],
                            [
                                "target_arch=='x64'",
                                {
                                    "include_dirs": [
                                        "<(node_root_dir)/deps/openssl/config/k8"
                                    ]
                                },
                            ],
                            [
                                "target_arch=='arm'",
                                {
                                    "include_dirs": [
                                        "<(node_root_dir)/deps/openssl/config/arm"
                                    ]
                                },
                            ],
                        ],
                    },
                ],
            ],
        }
    ]
}