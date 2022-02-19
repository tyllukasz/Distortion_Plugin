#include "TransferFunctions.h"

#define _USE_MATH_DEFINES
#include <math.h>


float arcTangens (double x, float slope) {
    return 2 / M_PI * atan(slope * x);
}
