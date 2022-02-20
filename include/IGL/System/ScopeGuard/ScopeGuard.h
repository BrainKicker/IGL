#pragma once

#define IGL_INCLUDE_STL
#include <IGL/Config.h>


namespace igl {


    class ScopeGuard {

        Functor mCleanup;

    public:

        ScopeGuard();
        ScopeGuard(const Functor& cleanup);
        ScopeGuard(Functor&& cleanup);
        ScopeGuard(ScopeGuard&& other);

        virtual ~ScopeGuard();

        ScopeGuard& operator=(const Functor& cleanup);
        ScopeGuard& operator=(Functor&& cleanup);
        ScopeGuard& operator=(ScopeGuard&& other);

        void dismiss();
    };
}