#ifndef _EXCEPTIONS_HPP_
#define _EXCEPTIONS_HPP_

#include <exception>

class MemoryException : public std::exception {
public:
    const char *what() const noexcept override {
        return "Memory error.";
    }
};

class InvalidArgumentException : public std::exception {
public:
    const char *what() const noexcept override {
        return "Invalid argument passed.";
    }
};

#endif
