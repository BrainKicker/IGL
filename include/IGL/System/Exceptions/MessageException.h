#pragma once

#include <IGL/igl_compile_includes.h>


namespace igl {


    class MessageException : public std::exception {

        std::string mMessage;

    public:

        MessageException(const std::string& message = "");

        const char* what() const noexcept override;
    };
}