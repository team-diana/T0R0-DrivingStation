#include "mathfunctions.h"
#include <math.h>


/*
 * The function that is implemented
 * Compy this on Geogebra after creating three sliders (a, b, c)
 * Se(x < (-(1 + a)) / b, -1, (-(1 + a)) / b < x < (-a) / b, -abs((b x + a)^c), (-a) / b < x < a / b, 0, a / b < x < (1 + a) / b, (b x - a)^c, x > (1 + a) / b, 1)
 */
double inputLinearityFunction (double x, float a, float b, int c)
{
    float minFactor = a / b;
    float maxFactor = (1+a) / b;

    double ans = 0;

    if (x < -maxFactor)
    {
        ans = -1;
    }
    else if ( x > -maxFactor && x < -minFactor)
    {
        // -abs((b x + a)^c)
        ans =  (double) pow ( (double)(-abs(b*x + a)) , c);
    }
    else if ( x > -minFactor && x < minFactor)
    {
        ans = 0;
    }
    else if ( x > minFactor && x < maxFactor)
    {
        ans = (double) pow( (double)(b x - a), c);
    }
    else
    {
        ans = 1;
    }

    return ans;
}
