#include "ovis/runtime/canvas.h"

#include "emscripten/html5.h"
#include "emscripten/html5_webgl.h"
#include <GLES2/gl2.h>

#include <cstdio>

struct Canvas {
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE webgl_context;
};

struct Canvas* ovis_canvas_create(struct Scene* scene, const char* canvas_id) {
  EmscriptenWebGLContextAttributes context_attributes;
  emscripten_webgl_init_context_attributes(&context_attributes);
  auto context = emscripten_webgl_create_context(canvas_id, &context_attributes);
  if (context < 0) {
    puts("Failed to create WebGL context");
  } else if (context == 0) {
    puts("Emscripten WebGL configuration problem");
  } else {
    puts("Successfully created WebGL context");
    emscripten_webgl_make_context_current(context);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
  }
  return new Canvas{ context };
}

void ovis_canvas_destroy(struct Canvas* canvas) {
  delete canvas;
}
