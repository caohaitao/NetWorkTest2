#include "stdafx.h"
#include "NetWorkMath.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MATH_E 2.718281828459
#define PRECISION 0.1

bool NetWorkMath::IsTwoFloatNear(float f1, float f2)
{
        if (fabs(f1-f2)<PRECISION){
                return true;
        }
        return false;
}

float NetWorkMath::SigMode(float f)
{
        return 1.0 / (1 + pow(MATH_E, -f));
}

#define RANDU() ((double)rand()/RAND_MAX)
#define EXPRAND() ((double)(-1.0)*log(1.0-((double)rand()/RAND_MAX)))

void NetWorkMath::randn(float * output, int n)
{
        int i;
        double y1, y2;
        srand(time(0));
        for (i = 0; i < n; i++)
        {
                do
                {
                        y1 = EXPRAND();
                        y2 = EXPRAND();
                } while (y2 <= ((1 - y1)*(1 - y1) / 2));
                *(output + i) = y1*((RANDU() < 0.5) ? 1 : -1);
        }
}
