#include <IGL/Config/Compile.h>
#include <IGL/System/Throwable/Error/ErrorWithStackTrace.h>


namespace igl {


    ErrorWithStackTrace::ErrorWithStackTrace(const std::string& message) : ErrorWithMessage(message) {

        const static int framesToSkip = 2; // one - stacktrace creation, two - error constructor
        const static int maxDepth = -1;    // no max depth

        mMessage.append(" at\n");
        mMessage.append(to_string(boost::stacktrace::basic_stacktrace(framesToSkip, maxDepth)));
    }

    ErrorWithStackTrace::ErrorWithStackTrace(std::string&& message) : ErrorWithMessage(std::move(message)) {

        const static int framesToSkip = 2; // one - stacktrace creation, two - error constructor
        const static int maxDepth = -1;    // no max depth

        mMessage.append(" at\n");
        mMessage.append(to_string(boost::stacktrace::basic_stacktrace(framesToSkip, maxDepth)));
    }
}