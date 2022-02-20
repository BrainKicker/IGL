#pragma once

#include <IGL/Config.h>

#include <IGL/Math.h>

#include <string>


namespace igl {


    class Color {
    public:

        static const Color white;       // { 1, 1, 1 }
        static const Color black;       // { 0, 0, 0 }
        static const Color transparent; // { 0, 0, 0, 0 }
        static const Color red;         // { 1, 0, 0 }
        static const Color green;       // { 0, 1, 0 }
        static const Color blue;        // { 0, 0, 1 }
        static const Color yellow;      // { 1, 1, 0 }
        static const Color magenta;     // { 1, 0, 1 }
        static const Color cyan;        // { 0, 1, 1 }
        static const Color brown;       // { 0.545, 0.271, 0.075 }
        static const Color purple;      // { 0.5, 0, 0.5 }
        static const Color orange;      // { 1, 0.647, 0 }
        static const Color deepskyblue; // { 0, 0.749, 1 }
        static const Color pink;        // { 1, 0.753, 0.796 }
        static const Color gold;        // { 1, 0.843, 0 }
        static const Color gray;        // { 0.5, 0.5, 0.5 }
        static const Color silver;      // { 0.753, 0.753, 0.753 }
        static const Color beige;       // { 0.961, 0.961, 0.863 }

        class ColorStringMode {

            bool mUpperCase;
            bool mWithHash;
            bool mIncludeA;

            ColorStringMode(bool upperCase, bool withHash, bool includeA);

        public:

            static const ColorStringMode rrggbb, RRGGBB;
            static const ColorStringMode rrggbbaa, RRGGBBAA;
            static const ColorStringMode h_rrggbb, h_RRGGBB;
            static const ColorStringMode h_rrggbbaa, h_RRGGBBAA;

            bool upperCase() const;
            bool withHash() const;
            bool includeA() const;
        };

        float r, g, b, a;

        static Color fromBytes(ubyte r, ubyte g, ubyte b, ubyte a = 255);
        static Color fromIntRGBA(uint color);
        static Color fromIntRGB(uint color);
        static Color fromString(const std::string& str);
        static Color fromString(const char* cstr);

        static uint toIntRGBA(const Color& color);
        static uint toIntRGB(const Color& color);
        static iglm::Vector3 toVec3(const Color& color);
        static iglm::Vector3 toVec4(const Color& color);
        static std::string toString(const Color& color, ColorStringMode mode = ColorStringMode::h_RRGGBBAA);

        static Color mix(const Color& c1, const Color& c2);
        template <typename Iterator>
        static Color mix(const Iterator& begin, const Iterator& end);
        template <typename Iterable>
        static Color mix(const Iterable& colors);
        static Color mix(const std::initializer_list<Color>& colors);

        static Color transit(const Color& c1, const Color& c2, float percent);

        Color();
        Color(float r, float g, float b, float a = 1);
        Color(const iglm::Vector3& v3);
        Color(const iglm::Vector4& v4);
        Color(const Color& other);

        Color& operator=(const iglm::Vector3& v3);
        Color& operator=(const iglm::Vector4& v4);
        Color& operator=(const Color& other);

        ubyte rByte() const;
        ubyte gByte() const;
        ubyte bByte() const;
        ubyte aByte() const;

        uint toIntRGBA() const;
        uint toIntRGB() const;
        iglm::Vector3 toVec3() const;
        iglm::Vector3 toVec4() const;
        std::string toString(ColorStringMode mode = ColorStringMode::h_RRGGBBAA) const;
    };
}