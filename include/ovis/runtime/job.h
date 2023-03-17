#pragma once

#include "ovis/runtime/resource.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef bool (*JobFunction)(struct Scene*);
typedef struct {
    const char* name;
    JobFunction function;
    int32_t resource_access_count;
    ResourceAccess* resource_access;
    int32_t dependency_count;
    const char** dependencies;
} Job;

bool register_job(const char* name, JobFunction function, int32_t resource_access_count, const ResourceAccess resource_access[]);
bool add_job_dependency(const char* dependency, const char* job);
const Job* get_job(const char* name);
bool deregister_job(const char* name);

#ifdef __cplusplus
}
#endif
