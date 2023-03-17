#pragma once

#include <exception>
#include <string>


class GrafException : public std::exception {
    std::string message;
public:
    GrafException(std::string msg) : message(msg) {}
    virtual const char* what() const throw() {
        return message.c_str();
    }
};

