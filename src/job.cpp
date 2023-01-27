#include "ovis/runtime/job.h"
#include "job.hpp"

std::unordered_map<std::string, JobFunction> JOBS;

bool register_job(const char* id, JobFunction function) {
  if (JOBS.contains(id)) {
    return false;
  }

  JOBS.insert(std::make_pair(id, function));
  return true;
}

JobFunction get_job(const char* id) {
  const auto job = JOBS.find(id);
  if (job == JOBS.end()) {
    return nullptr;
  } else {
    return job->second;
  }
}

bool deregister_job(const char* id) {
  if (!JOBS.contains(id)) {
    return false;
  }

  JOBS.erase(id);
  return true;
}
