#include "ovis/runtime/canvas.h"

#include "emscripten/html5.h"
#include "emscripten/html5_webgl.h"
#include "ovis/runtime/input_events.h"
#include "ovis/runtime/job.h"
#include "ovis/runtime/scene.h"
#include "ovis/runtime/symbols.h"
#include "scene.hpp"
#include <GLES2/gl2.h>

#include <cstdio>

struct Canvas {
    char* id;
    IndexedComponentStorage::Id::Type viewport_id;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE webgl_context;
};

EM_BOOL on_key_down(int event_type, const EmscriptenKeyboardEvent* keyboard_event, void* user_data) { return true; }

EM_BOOL on_mouse_move(int event_type, const EmscriptenMouseEvent* mouse_event, void* user_data) {
    auto scene = static_cast<Scene*>(user_data);
    const float x = mouse_event->targetX;
    const float y = mouse_event->targetY;
    const float dx = mouse_event->movementX;
    const float dy = mouse_event->movementY;
    auto mouse_move_storage = scene->get_event_storage(RESOURCE_ID(TYPE(ovis, runtime, MouseMoveEvent)));
    MouseMoveEvent event{
        .position = {x, y},
        .delta = {dx, dy},
    };
    mouse_move_storage->emit(&event);
    return true;
}

EM_BOOL on_mouse_button(int event_type, const EmscriptenMouseEvent* mouse_event, void* user_data) {
    auto scene = static_cast<Scene*>(user_data);
    auto mouse_move_storage = scene->get_event_storage(RESOURCE_ID(TYPE(ovis, runtime, MouseButtonEvent)));
    MouseButtonEvent event{
        .position = {static_cast<float>(mouse_event->targetX), static_cast<float>(mouse_event->targetY)},
        .button = mouse_event->button,
        .pressed = event_type == EMSCRIPTEN_EVENT_MOUSEDOWN,
    };
    mouse_move_storage->emit(&event);
    return true;
}

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

    auto viewport_id = scene->add_viewport();

    double canvas_css_width;
    double canvas_css_height;
    if (emscripten_get_element_css_size(canvas_id, &canvas_css_width, &canvas_css_height) == EMSCRIPTEN_RESULT_SUCCESS && (canvas_css_width > 0 && canvas_css_height > 0)) {
        TYPE(ovis, runtime, ViewportDimensions)
        dimensions;
        dimensions[0] = canvas_css_width;
        dimensions[1] = canvas_css_height;
        scene->get_indexed_component_storage(RESOURCE_ID(TYPE(ovis, runtime, ViewportDimensions)))->emplace(viewport_id, &dimensions);
    }

    emscripten_set_mousemove_callback(canvas_id, scene, 0, on_mouse_move);
    emscripten_set_mousedown_callback(canvas_id, scene, 0, on_mouse_button);
    emscripten_set_mouseup_callback(canvas_id, scene, 0, on_mouse_button);

    return new Canvas{
        .id = strdup(canvas_id),
        .viewport_id = viewport_id,
        .webgl_context = context,
    };
}

void ovis_canvas_destroy(struct Canvas* canvas) {
    emscripten_set_mousemove_callback(canvas->id, nullptr, 0, nullptr);
    emscripten_set_mousedown_callback(canvas->id, nullptr, 0, nullptr);
    emscripten_set_mouseup_callback(canvas->id, nullptr, 0, nullptr);
    free(canvas->id);
    delete canvas;
}

bool clear(void** input_components, void**) {
    auto clear_color = *((TYPE(ovis, runtime, Vec4F)*)input_components[0]);
    glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
    return true;
}

bool clear_framebuffer(struct Scene* scene) {
    const int32_t components[] = {RESOURCE_ID(TYPE(ovis, runtime, ClearColor))};
    return ovis_scene_iterate(scene, 1, components, 0, nullptr, clear);
}

__attribute__((constructor)) void setup_clear_framebuffer_job() {
    register_job("ovis/runtime/clearFramebuffer", &clear_framebuffer, 0, nullptr);
}

RESOURCE_IMPL_WITH_INFO(ovis, runtime, ClearColor, RESOURCE_KIND_VIEWPORT_COMPONENT, TYPE_INFO(TYPE(ovis, runtime, Vec4F)));
RESOURCE_IMPL_WITH_INFO(ovis, runtime, ViewportDimensions, RESOURCE_KIND_VIEWPORT_COMPONENT, TYPE_INFO(TYPE(ovis, runtime, Vec2F)));
RESOURCE_IMPL_WITH_INFO(ovis, runtime, ProjectionMatrix, RESOURCE_KIND_VIEWPORT_COMPONENT, TYPE_INFO(TYPE(ovis, runtime, Mat4x4F)));
RESOURCE_IMPL_WITH_INFO(ovis, runtime, ViewMatrix, RESOURCE_KIND_VIEWPORT_COMPONENT, TYPE_INFO(TYPE(ovis, runtime, Mat3x4F)));
