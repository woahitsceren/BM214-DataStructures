#include "PrecondViolatedExcep.h"

// Constructor TANIMI BURAYA ALINDI
PrecondViolatedExcep::PrecondViolatedExcep(const std::string& message)
    : std::logic_error("Precondition Violated Exception: " + message) {}
