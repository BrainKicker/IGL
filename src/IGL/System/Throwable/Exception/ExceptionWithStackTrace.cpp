#include <IGL/Config/Compile.h>
#include <IGL/System/Throwable/Exception/ExceptionWithStackTrace.h>


namespace igl {


    ExceptionWithStackTrace::ExceptionWithStackTrace(const std::string& message) : ExceptionWithMessage(message) {

        const static int framesToSkip = 2; // one - stacktrace creation, two - exception constructor
        const static int maxDepth = -1;    // no max depth

        mMessage.append(" at\n");
        mMessage.append(to_string(boost::stacktrace::basic_stacktrace(framesToSkip, maxDepth)));
    }

    ExceptionWithStackTrace::ExceptionWithStackTrace(std::string&& message) : ExceptionWithMessage(std::move(message)) {

        const static int framesToSkip = 2; // one - stacktrace creation, two - exception constructor
        const static int maxDepth = -1;    // no max depth

        mMessage.append(" at\n");
        mMessage.append(to_string(boost::stacktrace::basic_stacktrace(framesToSkip, maxDepth)));
    }
}