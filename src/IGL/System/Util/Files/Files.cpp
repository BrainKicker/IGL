#include <IGL/Config/Compile.h>
#include <IGL/System/Util/Files/Files.h>


namespace igl {


    std::string Files::readFile(const std::string& filename) throws(std::ios_base::failure) {
        std::ifstream in;
        in.exceptions(std::ios_base::badbit);
        in.open(filename);
        std::stringstream buff;
        buff.exceptions(std::ios_base::failbit);
        buff << in.rdbuf();
        return std::move(buff).str();
    }
}