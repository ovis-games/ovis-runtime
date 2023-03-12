#include "scheduler.hpp"
#include "job.hpp"

Scheduler::Scheduler() {
  m_jobs.reserve(JOBS.size());
  for (const auto& [name, job] : JOBS) {
    m_jobs.push_back(job.function);
  }
}

void Scheduler::run_jobs(struct Scene* scene) {
  for (const auto& job_function : m_jobs) {
    job_function(scene);
  }
}
