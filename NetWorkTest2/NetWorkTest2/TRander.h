#pragma once
class TRander
{
public:
        static TRander * GetControl();
        ~TRander();
        static void Clear();
        int GetARandNumber(int low, int high);
        void GetRandNumbers(float * outs, int fsize);
        float GetAFBetwen0To1();
        float GetAFBetwenLowToHigh(float low, float high);
        void GetAverageRandNumbers(float * outs, int fsize);
        double _uniform(double min, double max);
protected:
        void Init();
        TRander();
        static TRander * m_control;
};

