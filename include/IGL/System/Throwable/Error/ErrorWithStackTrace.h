#pragma once

#include <IGL/Config.h>

#include <IGL/System/Throwable/Error/ErrorWithMessage.h>


namespace igl {


    // abstract
    class ErrorWithStackTrace : public ErrorWithMessage {
    protected:
        ErrorWithStackTrace(const std::string& message = "");
        ErrorWithStackTrace(std::string&& message = "");
    };
}