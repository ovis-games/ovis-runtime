#pragma once

#include <vector>
#include "ovis/runtime/job.h"

class Scheduler {
public:
  Scheduler();

  void run_jobs();

private:
  std::vector<JobFunction> m_jobs;
};
