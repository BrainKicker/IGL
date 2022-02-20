#pragma once

#define IGL_INCLUDE_GL_MATH
#include <IGL/Config.h>


namespace igl {
    namespace math {


        template <int L, typename T = float>
        using Vector = glm::vec<L, T>;

        template <int C, int R, typename T = float>
        using Matrix = glm::mat<C, R, T>;

        using Vector1 = glm::vec1;
        using Vector2 = glm::vec2;
        using Vector3 = glm::vec3;
        using Vector4 = glm::vec4;

        using Matrix1x1 = glm::mat<1, 1, float>;
        using Matrix1x2 = glm::mat<1, 2, float>;
        using Matrix1x3 = glm::mat<1, 3, float>;
        using Matrix1x4 = glm::mat<1, 4, float>;
        using Matrix1 = glm::mat<1, 1, float>;

        using Matrix2x1 = glm::mat<2, 1, float>;
        using Matrix2x2 = glm::mat<2, 2, float>;
        using Matrix2x3 = glm::mat<2, 3, float>;
        using Matrix2x4 = glm::mat<2, 4, float>;
        using Matrix2 = glm::mat<2, 2, float>;

        using Matrix3x1 = glm::mat<3, 1, float>;
        using Matrix3x2 = glm::mat<3, 2, float>;
        using Matrix3x3 = glm::mat<3, 3, float>;
        using Matrix3x4 = glm::mat<3, 4, float>;
        using Matrix3 = glm::mat<3, 3, float>;

        using Matrix4x1 = glm::mat<4, 1, float>;
        using Matrix4x2 = glm::mat<4, 2, float>;
        using Matrix4x3 = glm::mat<4, 3, float>;
        using Matrix4x4 = glm::mat<4, 4, float>;
        using Matrix4 = glm::mat<4, 4, float>;


        template <int L, typename T>
        T length(const Vector<L, T>& v) {
            return glm::length(v);
        }


        template <int L, typename T>
        T distance(const Vector<L, T>& p0, const Vector<L, T>& p1) {
            return glm::distance(p0, p1);
        }


        template <int C, int R, typename T>
        T determinant(const Matrix<C, R, T>& m) {
            return glm::determinant(m);
        }


        template <int L, typename T>
        const T* valuePtr(const Vector<L, T>& v) {
            return glm::value_ptr(v);
        }


        template <int C, int R, typename T>
        const T* valuePtr(const Matrix<C, R, T>& m) {
            return glm::value_ptr(m);
        }
    }
}


namespace iglm = igl::math;