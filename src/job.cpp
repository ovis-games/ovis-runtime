#include "ovis/runtime/job.h"
#include "job.hpp"

std::unordered_map<std::string, Job> JOBS;

bool register_job(const char* name, JobFunction function, int32_t resource_access_count, const ResourceAccess resource_access[]) {
    if (JOBS.contains(name)) {
        return false;
    }

    printf("registering job: %s\n", name);
    Job job{
        .name = name,
        .function = function,
        .resource_access_count = 0,
        .resource_access = nullptr,
        .dependency_count = 0,
        .dependencies = nullptr,
    };
    JOBS.insert(std::make_pair(name, job));
    return true;
}

const Job* get_job(const char* name) {
    const auto job = JOBS.find(name);
    if (job == JOBS.end()) {
        return nullptr;
    } else {
        return &job->second;
    }
}

bool deregister_job(const char* name) {
    if (!JOBS.contains(name)) {
        return false;
    }

    JOBS.erase(name);
    return true;
}
