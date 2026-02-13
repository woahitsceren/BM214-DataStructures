// NotFoundException.cpp
// Implementation of NotFoundException class

#include "NotFoundException.h"

// Constructor: Custom exception message handling
NotFoundException::NotFoundException(const std::string& message)
    : std::logic_error("Not Found Exception: " + message) {}
