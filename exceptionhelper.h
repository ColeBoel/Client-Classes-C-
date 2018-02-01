#pragma once

#include <stdexcept>

class HttpRequestException : public std::exception
{
private:
    std::string msg;

public:
    HttpRequestException(const std::string& message = "") : msg(message)
    {
    }

    const char * what() const throw()
    {
        return msg.c_str();
    }
};
