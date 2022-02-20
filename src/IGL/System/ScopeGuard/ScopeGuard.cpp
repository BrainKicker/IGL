#include <IGL/Config/Compile.h>
#include <IGL/System/ScopeGuard/ScopeGuard.h>


namespace igl {


    ScopeGuard::ScopeGuard() : mCleanup(nullptr) {}

    ScopeGuard::ScopeGuard(const Functor& cleanup) : mCleanup(cleanup) {}

    ScopeGuard::ScopeGuard(Functor&& cleanup) : mCleanup(std::move(cleanup)) {}

    ScopeGuard::ScopeGuard(ScopeGuard&& other) : mCleanup(std::move(other.mCleanup)) {}



    ScopeGuard::~ScopeGuard() {
        if (mCleanup != nullptr)
            mCleanup();
    }



    ScopeGuard& ScopeGuard::operator=(const Functor& cleanup) {
        mCleanup = cleanup;
        return *this;
    }

    ScopeGuard& ScopeGuard::operator=(Functor&& cleanup) {
        mCleanup = std::move(cleanup);
        return *this;
    }

    ScopeGuard& ScopeGuard::operator=(ScopeGuard&& other) {
        mCleanup = std::move(other.mCleanup);
        return *this;
    }



    void ScopeGuard::dismiss() {
        mCleanup = nullptr;
    }
}