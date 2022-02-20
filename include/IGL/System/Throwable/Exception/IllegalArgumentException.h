#pragma once

#include <IGL/Config.h>

#include <IGL/System/Throwable/Exception/ExceptionWithStackTrace.h>


namespace igl {


    class IllegalArgumentException : public ExceptionWithStackTrace {
    public:
        IllegalArgumentException(const std::string& message);
        IllegalArgumentException(std::string&& message);
    };
}