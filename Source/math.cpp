﻿#include "math.h"

#include <algorithm>

void get_slope(int x1, int y1, int x2, int y2, float* dx, float* dy)
{
    int steps = std::max(abs(x1 - x2), abs(y1 - y2));
    if (steps == 0)
    {
        *dx = *dy = 0;
        return;
    }
    *dx = x2 - x1;
    *dx /= steps;
    *dy = y2 - y1;
    *dy /= steps;
}
