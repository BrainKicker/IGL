#pragma once

#include <IGL/Config.h>

#include <IGL/System/Throwable/Exception/Exception.h>

#include <string>


namespace igl {


    // abstract
    class ExceptionWithMessage : public Exception {

    protected:

        std::string mMessage;

        ExceptionWithMessage(const std::string& message = "");
        ExceptionWithMessage(std::string&& message = "");

    public:

        const char* what() const noexcept override;
    };
}