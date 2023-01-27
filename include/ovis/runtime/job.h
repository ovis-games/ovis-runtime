#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef bool(*JobFunction)();
struct Job {
  JobFunction function;
  const char* id;
};

bool register_job(const char* id, JobFunction function);
JobFunction get_job(const char* id);
bool deregister_job(const char* id);

#ifdef __cplusplus
}
#endif
