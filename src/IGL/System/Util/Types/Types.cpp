#include <IGL/Config/Compile.h>
#include <IGL/System/Util/Types/Types.h>


namespace igl {
    namespace Types {


        std::string demangle(const std::string& name) {

            int status = 0;

            std::unique_ptr<char, std::function<void(char*)>> res {
                    abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status),
                    std::free
            };

            return status == 0 ? res.get() : name;
        }
    }
}