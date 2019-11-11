
#pragma once
#ifndef __CS123COMMON_H__
#define __CS123COMMON_H__

#include <math.h>

// from http://en.wikipedia.org/wiki/Assertion_(computing)
#define COMPILE_TIME_ASSERT(pred) switch(0){case 0:case pred:;}

typedef float REAL;

#define IMAGE_WIDTH 256
#define IMAGE_HEIGHT 256

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MAX(a, b) (a) > (b) ? (a) : (b)

// ---------------------
// Common math utilities
// ---------------------

const float FLOAT_EPSILON = 1e-4f;
const double DOUBLE_EPSILON = 1e-8;

inline bool floatEpsEqual(float a, float b) {
    // If the difference between a and b is less than epsilon, they are equal
    return fabs(a - b) < FLOAT_EPSILON;
}

inline bool doubleEpsEqual(double a, double b)
{
    // If the difference between a and b is less than epsilon, they are equal
    return fabs(a - b) < DOUBLE_EPSILON;
}

#endif
