#pragma once

#include <IGL/Config.h>

#include <IGL/System/Throwable/Error/Error.h>

#include <string>


namespace igl {


    // abstract
    class ErrorWithMessage : public Error {

    protected:

        std::string mMessage;

        ErrorWithMessage(const std::string& message = "");
        ErrorWithMessage(std::string&& message = "");

    public:

        const char* what() const noexcept override;
    };
}