// NotFoundException.h
// Custom exception for not found errors

#ifndef NOT_FOUND_EXCEPTION_H
#define NOT_FOUND_EXCEPTION_H

#include <stdexcept>
#include <string>

class NotFoundException : public std::logic_error {
public:
    explicit NotFoundException(const std::string& message = "Item not found");
};

#endif
