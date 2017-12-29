#include "stdafx.h"
#include "TRander.h"
#include <time.h>
#include <stdlib.h>


void TRander::Init()
{
        srand(time(0));
}

TRander::TRander()
{
}


TRander * TRander::m_control = 0;

TRander * TRander::GetControl()
{
        if (m_control == 0){
                m_control = new TRander();
                m_control->Init();
        }
        return m_control;
}

TRander::~TRander()
{
}

void TRander::Clear()
{
        if (m_control){
                delete m_control;
                m_control = 0;
        }
}

int TRander::GetARandNumber(int low, int high)
{
        int r = rand();
        r = r % (high - low);
        return r + low;
}

void TRander::GetRandNumbers(float * outs, int fsize)
{
        srand(time(0));
        for (int i = 0; i < fsize;i++) {
                //outs[i] = GetAFBetwen0To1();
			outs[i] = _uniform(-1.0,1.0);
        }
}

float TRander::GetAFBetwen0To1()
{
        int r = GetARandNumber(0, 10000000);
        return (float)r / 10000000;
}

float TRander::GetAFBetwenLowToHigh(float low, float high)
{
        float fsub = high - low;
        int isub = fsub * 1000;
        int ir = GetARandNumber(0, isub);
        float fr = (float)ir / 1000.0;
        return low + fr;
}

void TRander::GetAverageRandNumbers(float * outs, int fsize)
{
        float sub = 1.0 / fsize;
        for (int i = 0; i < fsize;i++) {
                float low = float(i*sub);
                float high = float(i + 1)*sub;
                outs[i] = GetAFBetwenLowToHigh(low, high);
        }
}
double TRander::_uniform(double min, double max) {
        long int seed = rand();
        double t = 0;
        seed = 2045 * (seed) + 1;
        seed = seed - (seed / 1048576) * 1048576;
        t = (seed) / 1048576.0;
        t = min + (max - min) * t;
        return t;
}