#include "ovis/runtime/canvas.h"

#include "emscripten/html5.h"
#include "emscripten/html5_webgl.h"
#include "ovis/runtime/job.h"
#include "ovis/runtime/scene.h"
#include "ovis/runtime/symbols.h"
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
  }
  return new Canvas{ context };
}

void ovis_canvas_destroy(struct Canvas* canvas) {
  delete canvas;
}

bool clear(void** input_components, void**) {
  auto clear_color = *((TYPE(ovis, runtime, Vec4F)*)input_components[0]);
  glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
  glClear(GL_COLOR_BUFFER_BIT);
  return true;
}

bool clear_framebuffer(struct Scene* scene) {
  const int32_t components[] = { RESOURCE_ID(TYPE(ovis, runtime, ClearColor)) };
  return ovis_scene_iterate(scene, 1, components, 0, nullptr, clear);
}

__attribute__((constructor)) void setup_clear_framebuffer_job() {
  register_job("ovis/runtime/clearFramebuffer", &clear_framebuffer, 0, nullptr);
}

SCENE_COMPONENT_IMPL_WITH_INFO(ovis, runtime, ClearColor, TYPE_INFO(TYPE(ovis, runtime, Vec4F)));
