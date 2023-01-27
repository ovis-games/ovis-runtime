#pragma once

#include "ovis/runtime/scene.h"
#include "scheduler.hpp"

class Scene {
  public:
    void tick(float delta_time);

  private:
    Scheduler m_scheduler;
};

