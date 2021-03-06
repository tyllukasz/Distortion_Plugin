#include "TransferFunctions.h"

#define _USE_MATH_DEFINES
#include <math.h>


float arcTangens (double x, float slope) {
    return 2 / M_PI * atan(slope * x);
}

float hardClip (double x, double shape) {
    auto result = shape * x;
    if(result > 0) {
        if(result < 1.f) return result;
        else return 1.f;
    }
    else {
        if(result > -1.f) return result;
        else return -1.f;
    }
}
