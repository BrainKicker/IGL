#pragma once

#define IGL_MACRO_THROWS
#include <IGL/Config.h>

#include <string>


namespace igl {
    namespace Files {


        std::string readFile(const std::string& filename) throws(std::ios_base::failure);
    }
}