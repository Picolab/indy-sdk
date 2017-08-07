{
  "targets": [
    {
      "target_name": "libindy",
      "sources": ["src/libindy.cc"],
      "defines": [
        "NAPI_DISABLE_CPP_EXCEPTIONS"
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
        "<!(node -p \"require('node-addon-api').gyp\")"
      ]
    }
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
