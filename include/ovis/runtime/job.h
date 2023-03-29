#pragma once

#include "ovis/runtime/resource.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
    JOB_KIND_SETUP,
    JOB_KIND_UPDATE,
} JobKind;

typedef bool (*JobFunction)(struct Scene*);
typedef struct {
    const char* name;
    JobFunction function;
    JobKind kind;
    int32_t resource_access_count;
    ResourceAccess* resource_access;
    int32_t dependency_count;
    const char** dependencies;
} Job;

bool register_job(const char* name, JobFunction function, JobKind kind, int32_t resource_access_count, const ResourceAccess resource_access[]);
bool add_job_dependency(const char* dependency, const char* job);
const Job* get_job(const char* name);
bool deregister_job(const char* name);

#ifdef __cplusplus
}
#endif
