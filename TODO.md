# TODOs

- outputter
  - implement 'outputter_writedata_withstate'
    - change the name to better reflect that it just makes data available, including to the
    renderer, or some stream, don't matter...
  - accepts mapped data, and sends it via the selected output method
  - may the renderer, or may be another medium, but doesn't matter, is purely a relay component
- cli
  - setup loaddatamaps in cli_getstate_fromargs
  - setup colormap in cli_getstate_fromargs
  - add proper error handling for a missing state in cli_verify_state
- renderer
  - takes mapped data, and renders it to the screen (default option)
  - set up an abstraction to a GenericRenderer interface
    - Generic Renderer (all renderers use these 3 steps)
      - setup phase (prepares the renderer for use)
      - render frame (takes mapped data, renders it)
      - teardown phase (cleans up everything)
    - OpenGL renderer
      - build off generic for OpenGL bindings in C
      - maybe variant for mac/linux/etc.
    - Vulkan renderer
      - once OpenGL works, add support for this