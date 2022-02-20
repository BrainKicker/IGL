#include <IGL/Config/Compile.h>
#include <IGL/System/Throwable/Exception/ExceptionWithMessage.h>


namespace igl {


    ExceptionWithMessage::ExceptionWithMessage(const std::string& message) : mMessage(message) {}

    ExceptionWithMessage::ExceptionWithMessage(std::string&& message) : mMessage(std::move(message)) {}



    const char* ExceptionWithMessage::what() const noexcept {
        return mMessage.c_str();
    }
}