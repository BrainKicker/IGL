#include <IGL/Config/Includes.h>

#include <cstdint>


namespace igl {


    using byte = int8_t;

    using ubyte = uint8_t;
    using uchar = uint8_t;
    using ushort = uint16_t;
    using uint = uint32_t;
    using ulong = uint64_t;

    using int8 = int8_t;
    using uint8 = uint8_t;
    using int16 = int16_t;
    using uint16 = uint16_t;
    using int32 = int32_t;
    using uint32 = uint32_t;
    using int64 = int64_t;
    using uint64 = uint64_t;

    using float4 = float;
    using float32 = float4;
    using float8 = double;
    using float64 = float8;
    using float10 = long double;
    using float80 = float10;

#ifdef IGL_INCLUDE_STL

    template <typename T>
    using uptr = std::unique_ptr<T>;
    template <typename T>
    using sptr = std::shared_ptr<T>;
    template <typename T>
    using wptr = std::weak_ptr<T>;

    template <typename T>
    using ref = std::reference_wrapper<T>;

    template <typename T>
    using Comparator = std::function<bool(const T&, const T&)>;

    template <typename T>
    using Instantiator = std::function<T()>;

    using Functor = std::function<void()>;

#endif // IGL_INCLUDE_STL
}