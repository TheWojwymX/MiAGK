#ifndef MIAGK_MATHTYPES_H
#define MIAGK_MATHTYPES_H

class Float3 {
public:
    union
    {
        struct {
            float x, y, z;
        };
        struct {
            float r, g, b;
        };
    };

    Float3(float x, float y, float z) : x(x), y(y), z(z)
    {
        r = x;
        g = y;
        b = z;
    }

    Float3() { }

    Float3 operator+(const Float3& other)
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    Float3 operator-(const Float3& other)
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    Float3 operator*(float s)
    {
        return {s * x, s * y, s * z};
    }

};


#endif //MIAGK_MATHTYPES_H
