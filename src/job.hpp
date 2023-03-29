#pragma once

#include <unordered_map>
#include <string>
#include "ovis/runtime/job.h"

extern std::unordered_map<std::string, Job> SETUP_JOB;
extern std::unordered_map<std::string, Job> JOBS;
