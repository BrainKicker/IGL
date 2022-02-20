#pragma once

#include <IGL/Config.h>

#include <IGL/System/Throwable/Exception/ExceptionWithMessage.h>


namespace igl {


    // abstract
    class ExceptionWithStackTrace : public ExceptionWithMessage {
    protected:
        ExceptionWithStackTrace(const std::string& message = "");
        ExceptionWithStackTrace(std::string&& message = "");
    };
}