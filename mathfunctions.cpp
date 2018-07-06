#include "mathfunctions.h"
#include <math.h>

/*math::math()
{

}*/

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
        ans =  (double) pow (( -(1+a) / b ), c);
    }
    else if ( x > -minFactor && x < minFactor)
    {
        ans = 0;
    }
    else if ( x > minFactor && x < maxFactor)
    {
        ans = (double) pow(( (1+a) / b ), c);
    }
    else
    {
        ans = 1;
    }

    return ans;
}
