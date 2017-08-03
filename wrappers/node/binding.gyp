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
  ]
}
