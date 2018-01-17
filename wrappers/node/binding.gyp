{
  "targets": [
    {
      "target_name": "libindy",
      "sources": [
        "src/libindy.cc"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "CLANG_CXX_LIBRARY": "libc++",
        "MACOSX_DEPLOYMENT_TARGET": "10.7",
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1
        },
      },
      
      "defines": [
      #   "NAPI_DISABLE_CPP_EXCEPTIONS" # KEEPME disabled exceptions
        "INDY_LOG_LEVEL=<!(if [ \"$indy_log_level\" != '' ]; then echo $indy_log_level; else echo 3; fi)"
      ],
      "include_dirs": [
        "include",
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "libraries": [
        "-L<(module_root_dir)/include",
        "-lindy"
      ],
      "dependencies": [
        # KEEPME until i understand why
        # "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "conditions": [
        [
          "OS == 'linux'",
          {
            "defines": ['IS_LINUX'],
            "include_dirs": []
          }
        ],
        [
          "OS == 'mac'",
          {
            "defines": ['IS_MACOS'],
            "include_dirs": []
          }
        ],
        [
          "OS == 'win'",
          {
            "defines": ['IS_WINDOWS'],
            "include_dirs": []
          }
        ]
      ]
    }
  ]
}
