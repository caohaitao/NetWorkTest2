// NetWorkTest2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include "NetWorkMath.h"
#include "TRander.h"

#define E 2.718281828459

#define SPEED 0.5
#define SPEED_LINE 0.1

typedef float f3[3];
typedef float nparam[3];
typedef float input[3];

float Multy(float ins[3], float ins2[3])
{
	float res = 0.0;
	for (int i = 0; i < 3;i++)
	{
		res += ins[i] * ins2[i];
	}
	return res;
}

float sigmod(float i)
{
	return 1.0 / (1 + pow(E, -i));
}

void PrintParams(nparam ws[3])
{
        for (int i = 0; i < 3; i++)
        {
                for (int j = 0; j < 3; j++)
                {
                        printf("%0.4f   ", ws[i][j]);
                }
                printf("\n");
        }
}
bool OneTime()
{
        input xs[4] = {
                { 0,0,1 },
                { 0,1,1 },
                { 1,0,1 },
                { 1,1,1 }
        };
        float results[4] = { 0,1,1,0 };
        nparam ws[3]/* = {
                    {-0.59,-0.33,0.34},
                    {0.59,0.33,-0.34},
                    {0.2,0.6,0.3}
                    }*/;

        float www[9];
        //NetWorkMath::randn(www, 9);
        //TRander::GetControl()->GetAverageRandNumbers(www, 9);
        TRander::GetControl()->GetRandNumbers(www,9);

        //for (int i = 0; i < 3; i++)
        //{
        //        for (int j = 0; j < 3; j++)
        //        {
        //                ws[i][j] = www[3 * i + j] / sqrt(1.5);
        //        }
        //}

        for (int i = 0; i < 3; i++)
        {
                for (int j = 0; j < 3; j++)
                {
                        ws[i][j] = www[3 * i + j] * 2 - 1;
                }
        }


        //ws[0][0] = 0.7569752;
        //ws[0][1] = 0.19939837;
        //ws[0][2] = 0.32948969;

        //ws[1][0] = -0.7099531;
        //ws[1][1] = -0.49206245;
        //ws[1][2] = -0.44755478;

        //ws[2][0] = 0.6046035;
        //ws[2][1] = -0.37673705;
        //ws[2][2] = 0.02429106;

        //ws[0][2] = 0.01;
        //ws[1][2] = 0.01;
        //ws[2][2] = 0.01;
        //NetWorkMath::randn(ws[2], 3);


        //PrintParams(ws);


        float as[3];
        float das[3];


        for (int k = 0; k < 300000; k++)
        {
                for (int i = 0; i < 4; i++)
                {
                        input & x = xs[i];
                        as[0] = sigmod(Multy(ws[0], x));
                        as[1] = sigmod(Multy(ws[1], x));
                        input as_layer2 = { as[0],as[1],1.0 };
                        as[2] = sigmod(Multy(as_layer2, ws[2]));
                         
                        das[2] = as[2] * (1 - as[2])*(results[i] - as[2]);
                        das[1] = as[1] * (1 - as[1])*ws[2][1] * das[2];
                        das[0] = as[0] * (1 - as[0])*ws[2][0] * das[2];

                        ws[2][0] += as[2] * (1 - as[2])*SPEED*as[0] * das[2];
                        ws[2][1] += as[2] * (1 - as[2])*SPEED*as[1] * das[2];
                        ws[2][2] += as[2] * (1 - as[2])*SPEED*1.0 * das[2];

                        ws[0][0] += as[0] * (1 - as[0])*SPEED*x[0] * das[0];
                        ws[0][1] += as[0] * (1 - as[0])*SPEED*x[1] * das[0];
                        ws[0][2] += as[0] * (1 - as[0])*SPEED*x[2] * das[0];

                        ws[1][0] += as[1] * (1 - as[1])*SPEED*x[0] * das[1];
                        ws[1][1] += as[1] * (1 - as[1])*SPEED*x[1] * das[1];
                        ws[1][2] += as[1] * (1 - as[1])*SPEED*x[2] * das[1];
                }
        }

        bool res = true;
        float outs[4];
        for (int i = 0; i < 4; i++)
        {
                input & x = xs[i];
                as[0] = sigmod(Multy(ws[0], x));
                as[1] = sigmod(Multy(ws[1], x));
                input as_layer2 = { as[0],as[1],1.0 };
                as[2] = sigmod(Multy(as_layer2, ws[2]));
                outs[i] = as[2];
                if (fabs(outs[i]-results[i])>0.2){
                        res = false;
                }
        }
        //printf("\n");
        //PrintParams(ws);
        printf("\n");
        printf("%0.4f  %0.4f  %0.4f  %0.4f\n", outs[0], outs[1], outs[2], outs[3]);

        return res;
}
bool OneTimeOutPutLine()
{
        input xs[4] = {
                { 0,0,1 },
                { 0,1,1 },
                { 1,0,1 },
                { 1,1,1 }
        };
        float results[4] = { 1,0,0,1 };
        nparam ws[3]/* = {
                    {-0.59,-0.33,0.34},
                    {0.59,0.33,-0.34},
                    {0.2,0.6,0.3}
                    }*/;

        float www[9];
        NetWorkMath::randn(www, 9);
        //TRander::GetControl()->GetRandNumbers(www, 9);

        for (int i = 0; i < 3; i++)
        {
                for (int j = 0; j < 3; j++)
                {
                        ws[i][j] = www[3 * i + j];
                        ws[i][j] = ws[i][j] / sqrt(1.5);
                }
        }


        //ws[0][2] = 0.01;
        //ws[1][2] = 0.01;
        //ws[2][2] = 0.01;
        //NetWorkMath::randn(ws[2], 3);


        //PrintParams(ws);


        float as[3];
        float das[3];


        for (int k = 0; k < 1000000; k++)
        {
                for (int i = 0; i < 4; i++)
                {
                        input & x = xs[i];
                        as[0] = sigmod(Multy(ws[0], x));
                        as[1] = sigmod(Multy(ws[1], x));
                        input as_layer2 = { as[0],as[1],1.0 };
                        //as[2] = sigmod(Multy(as_layer2, ws[2]));
                        as[2] = Multy(as_layer2, ws[2]);

                        das[2] = /*as[2] * (1 - as[2])**/(results[i] - as[2]);
                        das[1] = as[1] * (1 - as[1])*ws[2][1] * das[2];
                        das[0] = as[0] * (1 - as[0])*ws[2][0] * das[2];

                        ws[2][0] += /*as[2] * (1 - as[2])**/SPEED_LINE*as[0] * das[2];
                        ws[2][1] += /*as[2] * (1 - as[2])**/SPEED_LINE*as[1] * das[2];
                        ws[2][2] += /*as[2] * (1 - as[2])**/SPEED_LINE*1.0 * das[2];

                        ws[0][0] += as[0] * (1 - as[0])*SPEED*x[0] * das[0];
                        ws[0][1] += as[0] * (1 - as[0])*SPEED*x[1] * das[0];
                        ws[0][2] += as[0] * (1 - as[0])*SPEED*x[2] * das[0];

                        ws[1][0] += as[1] * (1 - as[1])*SPEED*x[0] * das[1];
                        ws[1][1] += as[1] * (1 - as[1])*SPEED*x[1] * das[1];
                        ws[1][2] += as[1] * (1 - as[1])*SPEED*x[2] * das[1];
                }
        }

        bool res = true;
        float outs[4];
        for (int i = 0; i < 4; i++)
        {
                input & x = xs[i];
                as[0] = sigmod(Multy(ws[0], x));
                as[1] = sigmod(Multy(ws[1], x));
                input as_layer2 = { as[0],as[1],1.0 };
                //as[2] = sigmod(Multy(as_layer2, ws[2]));
                as[2] = Multy(as_layer2, ws[2]);
                outs[i] = as[2];
                if (fabs(outs[i] - results[i])>0.2) {
                        res = false;
                }
        }
        //printf("\n");
        //PrintParams(ws);
        printf("\n");
        printf("%0.4f  %0.4f  %0.4f  %0.4f\n", outs[0], outs[1], outs[2], outs[3]);

        return res;
}
bool OneTimePython()
{
        input xs[4] = {
                { 0,0,1 },
                { 0,1,1 },
                { 1,0,1 },
                { 1,1,1 }
        };
        float results[4] = { 1,0,0,1 };
        nparam ws[3]/* = {
                    {-0.59,-0.33,0.34},
                    {0.59,0.33,-0.34},
                    {0.2,0.6,0.3}
                    }*/;

        float www[9];
        //NetWorkMath::randn(www, 9);
        TRander::GetControl()->GetRandNumbers(www, 9);

        for (int i = 0; i < 3; i++)
        {
                for (int j = 0; j < 3; j++)
                {
                        ws[i][j] = 2 * ws[i][j] - 1;
                }
        }
        ws[0][0] = 0.82518572;
        ws[0][1] = -0.73232911;
        ws[0][2] = -0.20876042;

        ws[1][0] = -0.63514666;
        ws[1][1] = 0.36820595;
        ws[1][2] = 0.03830064;

        ws[2][0] = 0.8951277;
        ws[2][1] = -0.61189705;
        ws[2][2] = -0.60260254;

        //ws[0][2] = 0.01;
        //ws[1][2] = 0.01;
        //ws[2][2] = 0.01;
        //NetWorkMath::randn(ws[2], 3);


        //PrintParams(ws);


        float as[3];
        float das[3][3];


        for (int k = 0; k < 1000000; k++)
        {
                memset(das, 0, sizeof(float) * 9);
                for (int i = 0; i < 4; i++)
                {
                        input & x = xs[i];
                        as[0] = sigmod(Multy(ws[0], x));
                        as[1] = sigmod(Multy(ws[1], x));
                        input as_layer2 = { as[0],as[1],1.0 };
                        as[2] = sigmod(Multy(as_layer2, ws[2]));

                        float delta = (results[i] - as[2]);
                        das[2][0] += delta*as[0];
                        das[2][1] += delta*as[1];
                        das[2][2] += delta;

                        das[0][0] += ws[2][0] * delta*as[0] * (1 - as[0])*x[0];
                        das[0][1] += ws[2][0] * delta*as[0] * (1 - as[0])*x[1];
                        das[0][2] += ws[2][0] * delta*as[0] * (1 - as[0])*x[2];

                        das[1][0] += ws[2][1] * delta*as[1] * (1 - as[1])*x[0];
                        das[1][1] += ws[2][1] * delta*as[1] * (1 - as[1])*x[1];
                        das[1][2] += ws[2][1] * delta*as[1] * (1 - as[1])*x[1];
                }

                for (int i = 0; i < 3;i++) {
                        for (int j = 0; j < 3;j++) {
                                das[i][j] = das[i][j] / 4.0;
                                ws[i][j] += SPEED*das[i][j];
                        }
                }
                
        }

        bool res = true;
        float outs[4];
        for (int i = 0; i < 4; i++)
        {
                input & x = xs[i];
                as[0] = sigmod(Multy(ws[0], x));
                as[1] = sigmod(Multy(ws[1], x));
                input as_layer2 = { as[0],as[1],1.0 };
                as[2] = sigmod(Multy(as_layer2, ws[2]));
                outs[i] = as[2];
                if (fabs(outs[i] - results[i])>0.2) {
                        res = false;
                }
        }
        //printf("\n");
        //PrintParams(ws);
        printf("\n");
        printf("%0.4f  %0.4f  %0.4f  %0.4f\n", outs[0], outs[1], outs[2], outs[3]);

        return res;
}
int main()
{
        float www[10000];
        TRander::GetControl()->GetRandNumbers(www, 10000);
        int a[10] = { 0 };
        for (int i = 0; i < 10000; i++) {
                int index = www[i] * 10;
                a[index]++;
        }
        for (int i = 0; i < 10; i++) {
                printf("i=%d:n=%d\n", i, a[i]);
        }
        return 1;
        //float a[9];
        //TRander::GetControl()->GetRandNumbers(a,9);

        //return 0;
        int whole_times = 40;
        int right_times = 0;
        for (int i = 0; i < whole_times;i++) {
                printf("test time %d\n", i);
                if (OneTime()){
                        right_times++;
                }
                
        }
        printf("whole times = %d,right times = %d\n", whole_times, right_times);
        return 0;
}

