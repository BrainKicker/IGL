#pragma once

#include <IGL/Config.h>

#include <IGL/System/Throwable/Error/ErrorWithStackTrace.h>


namespace igl {


    class RuntimeError : public ErrorWithStackTrace {
    public:
        RuntimeError(const std::string& message = "");
    };
}