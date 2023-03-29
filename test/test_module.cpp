#include "ovis/runtime.h"
#include "emscripten/html5.h"

extern "C" {

bool job(struct Scene* scene) {
  emscripten_console_log("job()");
  return true;
}

__attribute__((constructor)) void ovis_module_load() {
  register_job("test_module_job", &job, JOB_KIND_UPDATE, 0, nullptr);
}

__attribute__((destructor)) void ovis_module_unload() {
  deregister_job("test_module_job");
}

}
