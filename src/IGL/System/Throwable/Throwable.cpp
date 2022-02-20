#include <IGL/Config/Compile.h>
#include <IGL/System/Throwable/Throwable.h>

#include <IGL/System/Util/Types/Types.h>


namespace igl {


    void Throwable::print(std::ostream& out) const {
        out << "Thrown an instance of '" << Types::typeName(*this)
        << "'\n  what():  " << what() << std::endl;
    }
}