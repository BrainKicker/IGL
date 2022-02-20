#include <IGL/Config/Compile.h>
#include <IGL/System/Throwable/Error/RuntimeError.h>


namespace igl {


    RuntimeError::RuntimeError(const std::string& message) : ErrorWithStackTrace(message) {}
}