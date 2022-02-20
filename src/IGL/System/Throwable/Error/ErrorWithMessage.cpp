#include <IGL/Config/Compile.h>
#include <IGL/System/Throwable/Error/ErrorWithMessage.h>


namespace igl {


    ErrorWithMessage::ErrorWithMessage(const std::string& message) : mMessage(message) {}

    ErrorWithMessage::ErrorWithMessage(std::string&& message) : mMessage(std::move(message)) {}



    const char* ErrorWithMessage::what() const noexcept {
        return mMessage.c_str();
    }
}