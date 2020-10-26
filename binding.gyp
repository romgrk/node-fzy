{
  "targets": [
    {
      "target_name": "node_fzy",
      "sources": [
        "src/export.c",
        "src/module-js.c",
        "src/fzy/match.c",
      ],
      "libraries": [],
      "include_dirs" : [],
      "cflags": [
          # "<!@(pkg-config --cflags gobject-introspection-1.0 cairo) -Wall -g",
      ],
      "ldflags": [
          # "-Wl,-no-as-needed",
          # "<!@(pkg-config --libs gobject-introspection-1.0 cairo)",
      ],
    },
    {
        "target_name": "action_after_build",
        "type": "none",
        "dependencies": [ "<(module_name)" ],
        "copies": [
            {
                "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
                "destination": "<(module_path)"
            }
        ]
    }
  ]
}
