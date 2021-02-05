{
  "targets": [
    {
      "target_name": "file-checksum",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [
        "-fno-exceptions",
      ],
      "cflags_cc": [
        "-std=c++17"
      ],
      "sources": [
        "./src/sha256-checksum.cpp",
        "./src/index.cpp",
        '<!@(ls -1 ./src/*.cpp)',
        '<!@(ls -1 ./src/**/*.cpp)'
      ],
      'dependencies': [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include_dir\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      'conditions': [
        ['node_shared_openssl=="false"', {
          # so when "node_shared_openssl" is "false", then OpenSSL has been
          # bundled into the node executable. So we need to include the same
          # header files that were used when building node.
          'include_dirs': [
            '<(node_root_dir)/deps/openssl/openssl/include'
          ],
          "conditions" : [
            ['OS=="linux"', {
              "link-settings": {
                "ldflags": [
                  '-lssl',
                  '-lcrypto'
                ]
              }
            }],
            ["target_arch=='ia32'", {
              "include_dirs": [ "<(node_root_dir)/deps/openssl/config/piii" ]
            }],
            ["target_arch=='x64'", {
              "include_dirs": [ "<(node_root_dir)/deps/openssl/config/k8" ]
            }],
            ["target_arch=='arm'", {
              "include_dirs": [ "<(node_root_dir)/deps/openssl/config/arm" ]
            }]
          ]
        }]
      ]
    }
  ]
}