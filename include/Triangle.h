
#ifndef MIAGK_TRIANGLE_H
#define MIAGK_TRIANGLE_H


#include "mathTypes.h"

class Triangle {
public:
    Float3 v1, v2, v3;
    Float3 c1, c2, c3;

    Triangle(Float3 v1, Float3 v2, Float3 v3, Float3 c1, Float3 c2, Float3 c3);
};


#endif //MIAGK_TRIANGLE_H
