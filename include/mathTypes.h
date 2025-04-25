#ifndef MIAGK_MATHTYPES_H
#define MIAGK_MATHTYPES_H
#define M_PI 3.14159265358979323846

#include <cmath>

class Float3 {
public:
    union {
        struct {
            float x, y, z;
        };
        struct {
            float r, g, b;
        };
    };

    Float3(float x, float y, float z) : x(x), y(y), z(z) {
        r = x;
        g = y;
        b = z;
    }

    Float3() {}

    Float3 cross(const Float3 &other) const {
        return {
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
        };
    }

    void normalize() {
        float len = sqrt(x * x + y * y + z * z);
        if (len > 1e-4) {
            x /= len;
            y /= len;
            z /= len;
        } else {
            x = y = z = 0.0f;
        }
    }

    Float3 operator+(const Float3 &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Float3 operator-(const Float3 &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Float3 operator*(float s) const {
        return {s * x, s * y, s * z};
    }

    Float3 operator*(const Float3 &other) const {
        return {x * other.x, y * other.y, z * other.z};
    }

    float dot(const Float3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

};

class Float4 {
public:
    union {
        struct {
            float x, y, z, w;
        };
        struct {
            float r, g, b, a;
        };
    };

    Float4() {

    }

    Float4(const Float3& vector, float w)
    {
        x = vector.x;
        y = vector.y;
        z = vector.z;
        this->w = w;
    }

    Float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {

    }

    void normalize() {
        float len = sqrt(x * x + y * y + z * z + w * w);
        if (len > 1e-4f) {
            x /= len;
            y /= len;
            z /= len;
            w /= len;
        } else {
            x = y = z = w = 0.0f;
        }
    }

    Float4 operator+(const Float4 &other) const {
        return {x + other.x, y + other.y, z + other.z, w + other.w};
    }

    Float4 operator-(const Float4 &other) const {
        return {x - other.x, y - other.y, z - other.z, w - other.w};
    }

    Float4 operator*(float s) const {
        return {x * s, y * s, z * s, w * s};
    }

    Float4 operator*(const Float4 &other) const {
        return {x * other.x, y * other.y, z * other.z, w * other.w};
    }

    Float3 toFloat3() const {
        return Float3(x, y, z);
    }
};

class Float4x4 {
public:
    union {
        struct {
            Float4 rows[4];
        };
        float m[4][4]; // m[row][col]
        float flat[16]; // dla ewentualnego przesyłu do shaderów itp.
    };

    Float4x4() {
        for (int i = 0; i < 16; ++i)
            flat[i] = 0.0f;
    }

    Float4x4(const Float4 &r0, const Float4 &r1, const Float4 &r2, const Float4 &r3) {
        rows[0] = r0;
        rows[1] = r1;
        rows[2] = r2;
        rows[3] = r3;
    }

    Float4x4 operator+(const Float4x4 &other) const {
        Float4x4 result;
        for (int i = 0; i < 4; ++i) {
            result.rows[i] = rows[i] + other.rows[i];
        }
        return result;
    }

    Float4x4 operator-(const Float4x4 &other) const {
        Float4x4 result;
        for (int i = 0; i < 4; ++i) {
            result.rows[i] = rows[i] - other.rows[i];
        }
        return result;
    }

    Float4x4 operator*(const Float4x4 &other) const {
        Float4x4 result;
        Float4 col[4];
        for (int i = 0; i < 4; ++i) {
            col[i] = {other.m[0][i], other.m[1][i], other.m[2][i], other.m[3][i]};
        }
        for (int i = 0; i < 4; ++i) {
            result.m[i][0] =
                    rows[i].x * col[0].x + rows[i].y * col[0].y + rows[i].z * col[0].z + rows[i].w * col[0].w;
            result.m[i][1] =
                    rows[i].x * col[1].x + rows[i].y * col[1].y + rows[i].z * col[1].z + rows[i].w * col[1].w;
            result.m[i][2] =
                    rows[i].x * col[2].x + rows[i].y * col[2].y + rows[i].z * col[2].z + rows[i].w * col[2].w;
            result.m[i][3] =
                    rows[i].x * col[3].x + rows[i].y * col[3].y + rows[i].z * col[3].z + rows[i].w * col[3].w;
        }
        return result;
    }

    Float4 operator*(const Float4 &vec) const {
        return
                {
                        rows[0].x * vec.x + rows[0].y * vec.y + rows[0].z * vec.z + rows[0].w * vec.w,
                        rows[1].x * vec.x + rows[1].y * vec.y + rows[1].z * vec.z + rows[1].w * vec.w,
                        rows[2].x * vec.x + rows[2].y * vec.y + rows[2].z * vec.z + rows[2].w * vec.w,
                        rows[3].x * vec.x + rows[3].y * vec.y + rows[3].z * vec.z + rows[3].w * vec.w
                };
    }

    Float4 operator*(const Float3 &vec) const {
        Float4 extendedVec(vec.x, vec.y, vec.z, 1.0f);
        return (*this) * extendedVec;
    }

    Float4 &operator[](int index) {
        return rows[index];
    }

    const Float4 &operator[](int index) const {
        return rows[index];
    }

    Float4x4 transpose() const {
        Float4x4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result.m[i][j] = m[j][i];
        return result;
    }

    void setAsIdentity() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = (i == j) ? 1.0f : 0.0f;
    }
};

class Int3 {
public:
    int v1, v2, v3;

    Int3(int v1, int v2, int v3)
    {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }

};

inline Float3 operator*(float s, const Float3 &v) {
    return v * s;
}


#endif //MIAGK_MATHTYPES_H
