#include "ovis/runtime/job.h"
#include "job.hpp"

std::unordered_map<std::string, Job> JOBS;

bool register_job(const char* name, JobFunction function, JobKind kind, int32_t resource_access_count, const ResourceAccess resource_access[]) {
    if (JOBS.contains(name)) {
        return false;
    }

    auto resource_access_copy = new ResourceAccess[resource_access_count];
    memcpy(resource_access_copy, resource_access, sizeof(ResourceAccess) * resource_access_count);

    printf("registering job: %s\n", name);
    Job job{
        .name = name,
        .function = function,
        .kind = kind,
        .resource_access_count = resource_access_count,
        .resource_access = resource_access_copy,
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

    // TODO: free resources of job

    JOBS.erase(name);
    return true;
}
