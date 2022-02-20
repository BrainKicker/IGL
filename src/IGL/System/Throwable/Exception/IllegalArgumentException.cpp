#include <IGL/Config/Compile.h>
#include <IGL/System/Throwable/Exception/IllegalArgumentException.h>


namespace igl {


    IllegalArgumentException::IllegalArgumentException(const std::string& message) : ExceptionWithStackTrace(message) {}

    IllegalArgumentException::IllegalArgumentException(std::string&& message) : ExceptionWithStackTrace(std::move(message)) {}
}