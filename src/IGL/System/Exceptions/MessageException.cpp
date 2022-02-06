#include <IGL/System/Exceptions/MessageException.h>


namespace igl {


    MessageException::MessageException(const std::string& message) : mMessage(message) {}



    const char* MessageException::what() const noexcept {
        return mMessage.c_str();
    }
}