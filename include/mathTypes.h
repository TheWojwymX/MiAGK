#ifndef MIAGK_MATHTYPES_H
#define MIAGK_MATHTYPES_H

struct Float3
{
    float x;
    float y;
    float z;

    Float3 operator+(const Float3 &other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    Float3 operator*(float scalar) const
    {
        return {x * scalar, y * scalar, z * scalar};
    }
};


#endif //MIAGK_MATHTYPES_H
