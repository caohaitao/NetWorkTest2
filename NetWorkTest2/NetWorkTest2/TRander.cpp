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

float TRander::GetAFBetwen0To1()
{
        int r = GetARandNumber(0, 100);
        return (float)r / 100.0;
}

float TRander::GetAFBetwenLowToHigh(float low, float high)
{
        float fsub = high - low;
        int isub = fsub * 100;
        int ir = GetARandNumber(0, isub);
        float fr = (float)ir / 100.0;
        return low + fr;
}
