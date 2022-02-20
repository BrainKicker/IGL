#pragma once

#define IGL_MACRO_THROWS
#include <IGL/Config.h>

#include <exception>
#include <iostream>


namespace igl {


    // abstract
    class Throwable : public std::exception {
    protected:
        Throwable() = default;
    public:
        void print(std::ostream& out = std::cerr) const;
    };
}