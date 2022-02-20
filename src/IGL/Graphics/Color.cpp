#include <IGL/Config/Compile.h>
#include <IGL/Graphics/Color.h>


namespace igl {


    const Color::ColorStringMode Color::ColorStringMode::rrggbb     { false, false, false };
    const Color::ColorStringMode Color::ColorStringMode::RRGGBB     { true,  false, false };
    const Color::ColorStringMode Color::ColorStringMode::rrggbbaa   { false, false, true  };
    const Color::ColorStringMode Color::ColorStringMode::RRGGBBAA   { true,  false, true  };
    const Color::ColorStringMode Color::ColorStringMode::h_rrggbb   { false, true,  false };
    const Color::ColorStringMode Color::ColorStringMode::h_RRGGBB   { true,  true,  false };
    const Color::ColorStringMode Color::ColorStringMode::h_rrggbbaa { false, true,  true  };
    const Color::ColorStringMode Color::ColorStringMode::h_RRGGBBAA { true,  true,  true  };



    Color::ColorStringMode::ColorStringMode(bool upperCase, bool withHash, bool includeA)
    : mUpperCase(upperCase), mWithHash(withHash), mIncludeA(includeA) {}

    bool Color::ColorStringMode::upperCase() const {
        return mUpperCase;
    }

    bool Color::ColorStringMode::withHash() const {
        return mWithHash;
    }

    bool Color::ColorStringMode::includeA() const {
        return mIncludeA;
    }



    const Color Color::white       { 1, 1, 1 };
    const Color Color::black       { 0, 0, 0 };
    const Color Color::transparent { 0, 0, 0, 0 };
    const Color Color::red         { 1, 0, 0 };
    const Color Color::green       { 0, 1, 0 };
    const Color Color::blue        { 0, 0, 1 };
    const Color Color::yellow      { 1, 1, 0 };
    const Color Color::magenta     { 1, 0, 1 };
    const Color Color::cyan        { 0, 1, 1 };
    const Color Color::brown       { 0.545, 0.271, 0.075 };
    const Color Color::purple      { 0.5, 0, 0.5 };
    const Color Color::orange      { 1, 0.647, 0 };
    const Color Color::deepskyblue {0, 0.749, 1 };
    const Color Color::pink        { 1, 0.753, 0.796 };
    const Color Color::gold        { 1, 0.843, 0 };
    const Color Color::gray        { 0.5, 0.5, 0.5 };
    const Color Color::silver      { 0.753, 0.753, 0.753 };
    const Color Color::beige       { 0.961, 0.961, 0.863 };



    Color Color::fromBytes(ubyte r, ubyte g, ubyte b, ubyte a) {
        return Color(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
    }

    Color Color::fromIntRGBA(uint color) {
        ubyte r, g, b, a;
        a = color & 0xFF;
        color >>= 8;
        b = color & 0xFF;
        color >>= 8;
        g = color & 0xFF;
        color >>= 8;
        r = color & 0xFF;
        return fromBytes(r, g, b, a);
    }

    Color Color::fromIntRGB(uint color) {
        ubyte r, g, b;
        b = color & 0xFF;
        color >>= 8;
        g = color & 0xFF;
        color >>= 8;
        r = color & 0xFF;
        return fromBytes(r, g, b);
    }

    Color Color::fromString(const std::string& str) {
        return fromString(str.c_str());
    }

    Color Color::fromString(const char* cstr) {

        if (*cstr == '#')
            ++cstr;

        int len = [&]() -> int {

            int len = 0;

            while (len < 8) {
                char c = cstr[len];
                if (c == '\0')
                    break;
                if (!(c >= '0' && c <= '9')
                    && !(c >= 'A' && c <= 'F')
                    && !(c >= 'a' && c <= 'f'))
                    break;
                ++len;
            }

            return len;
        }();

        bool shortColor;
        switch (len) {
            case 3:
            case 4:
                shortColor = true;
                break;
            case 6:
            case 8:
                shortColor = false;
                break;
            default:
                return transparent;
        }

        uint color = 0;
        for (int i = 0; i < len; ++i) {

            char c = cstr[i];

            if (c >= '0' && c <= '9')
                c -= '0';
            else if (c >= 'A' && c <= 'F')
                c -= 'A' - 10;
            else // c >= 'a' && c <= 'f'
                c -= 'a' - 10;

            color <<= 4;
            color |= c;

            if (shortColor) {
                color <<= 4;
                color |= c;
            }
        }

        return len == 4 || len == 8 ? fromIntRGBA(color) : fromIntRGB(color);
    }



    uint Color::toIntRGBA(const Color& color) {
        return (toIntRGB(color) << 8) | color.aByte();
    }

    uint Color::toIntRGB(const Color& color) {
        uint result = 0;
        result |= color.rByte();
        result <<= 8;
        result |= color.gByte();
        result <<= 8;
        result |= color.bByte();
        return result;
    }

    iglm::Vector3 Color::toVec3(const Color& color) {
        return iglm::Vector3(color.r, color.g, color.b);
    }

    iglm::Vector3 Color::toVec4(const Color& color) {
        return iglm::Vector4(color.r, color.g, color.b, color.a);
    }

    std::string Color::toString(const Color& color, ColorStringMode mode) {

        std::string result = mode.withHash() ? "#" : "";

        static const std::function<char(byte)> get0xChar = [&](byte c) -> char {
            if (c < 10)
                return '0' + c;
            return (mode.upperCase() ? 'A' : 'a') - 10 + c;
        };
        static const std::function<void(ubyte)> addComponent = [&](ubyte component) {
            char lowPart = get0xChar(component & 0xF);
            result.push_back(get0xChar((component >> 4) & 0xf));
            result.push_back(lowPart);
        };

        addComponent(color.rByte());
        addComponent(color.gByte());
        addComponent(color.bByte());
        if (mode.includeA())
            addComponent(color.aByte());

        return result;
    }



    Color Color::mix(const Color& c1, const Color& c2) {
        return Color{ (c1.r + c2.r)/2, (c1.g + c2.g)/2, (c1.b + c2.b)/2, (c1.a + c2.a)/2 };
    }

    template <typename Iterator>
    Color Color::mix(const Iterator& begin, const Iterator& end) {
        int count = 0;
        Color result { 0, 0, 0, 0 };
        for (auto iter = begin; iter != end; ++iter, ++count) {
            result.r += iter->r;
            result.g += iter->g;
            result.b += iter->b;
            result.a += iter->a;
        }
        result.r /= count;
        result.g /= count;
        result.b /= count;
        result.a /= count;
        return result;
    }

    template <typename Iterable>
    Color Color::mix(const Iterable& colors) {
        return mix(colors.begin(), colors.end());
    }

    Color Color::mix(const std::initializer_list<Color>& colors) {
        return mix(colors.begin(), colors.end());
    }



    Color Color::transit(const Color& c1, const Color& c2, float percent) {
        return Color{
            c1.r + (c2.r - c1.r) * percent,
            c1.g + (c2.g - c1.g) * percent,
            c1.b + (c2.b - c1.b) * percent,
            c1.a + (c2.a - c1.a) * percent
        };
    }



    Color::Color() : Color(0, 0, 0) {}

    Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

    Color::Color(const iglm::Vector3& v3) : Color(v3.r, v3.g, v3.b) {}

    Color::Color(const iglm::Vector4& v4) : Color(v4.r, v4.g, v4.b, v4.a) {}

    Color::Color(const Color& other) : Color(other.r, other.g, other.b, other.a) {}



    Color& Color::operator=(const iglm::Vector3& v3) {
        r = v3.r;
        g = v3.g;
        b = v3.b;
        a = 1;
        return *this;
    }

    Color& Color::operator=(const iglm::Vector4& v4) {
        r = v4.r;
        g = v4.g;
        b = v4.b;
        a = v4.a;
        return *this;
    }

    Color& Color::operator=(const Color& other) {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
        return *this;
    }



    ubyte Color::rByte() const {
        return (ubyte) std::round(r * 255);
    }

    ubyte Color::gByte() const {
        return (ubyte) std::round(g * 255);
    }

    ubyte Color::bByte() const {
        return (ubyte) std::round(b * 255);
    }

    ubyte Color::aByte() const {
        return (ubyte) std::round(a * 255);
    }



    uint Color::toIntRGBA() const {
        return toIntRGBA(*this);
    }

    uint Color::toIntRGB() const {
        return toIntRGB(*this);
    }

    iglm::Vector3 Color::toVec3() const {
        return toVec3(*this);
    }

    iglm::Vector3 Color::toVec4() const {
        return toVec4(*this);
    }

    std::string Color::toString(ColorStringMode mode) const {
        return toString(*this, mode);
    }
}