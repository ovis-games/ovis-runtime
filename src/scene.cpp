#include "scene.hpp"

struct Scene* ovis_scene_create() {
  return new Scene();
}

void ovis_scene_tick(struct Scene* scene, float delta_time) {
  scene->tick(delta_time);
}

void ovis_scene_destroy(struct Scene* scene) {
  delete scene;
}

void Scene::tick(float delta_time) {
  m_scheduler.run_jobs();
}
