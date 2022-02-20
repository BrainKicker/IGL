#pragma once

#include <IGL/Config.h>

#include <string>


namespace igl {
    namespace Types {


        std::string demangle(const std::string& name);

        template <typename T>
        std::string typeName(const T& t) {
            return demangle(typeid(t).name());
        }

        template <typename T>
        std::string typeName() {
            return demangle(typeid(T).name());
        }
    }
}