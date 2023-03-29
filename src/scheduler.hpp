#pragma once

#include "ovis/runtime/job.h"
#include <vector>

class Scheduler {
  public:
    Scheduler(JobKind job_kind);

    void run_jobs(struct Scene* scene);

  private:
    std::vector<JobFunction> m_jobs;
};
