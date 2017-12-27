// NetWorkTest2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include "NetWorkMath.h"

#define E 2.718281828459

#define SPEED 0.01

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

int main()
{
	input xs[4] = {
		{0,0,1},
		{0,1,1},
		{1,0,1},
		{1,1,1}
	};
	float results[4] = { 1,0,0,1 };
	nparam ws[3]/* = {
		{-0.59,-0.33,0.34},
		{0.59,0.33,-0.34},
		{0.2,0.6,0.3}
	}*/;

	float www[9];
	NetWorkMath::randn(www, 9);

	for (int i = 0; i < 3;i++)
	{
		for (int j = 0; j < 3;j++)
		{
			ws[i][j] = www[3 * i + j];
			ws[i][j] = ws[i][j] / sqrt(1.5);
		}
	}
	//ws[0][2] = 0.01;
	//ws[1][2] = 0.01;
	//ws[2][2] = 0.01;
	//NetWorkMath::randn(ws[2], 3);
	for (int i = 0; i < 3;i++)
	{
		for (int j = 0; j < 3;j++)
		{
			printf("%0.4f   ", ws[i][j]);
		}
		printf("\n");
	}


	float as[3];
	float das[3];


	for (int k = 0; k < 10000000;k++)
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

	float outs[4];
	for (int i = 0; i < 4; i++)
	{
		input & x = xs[i];
		as[0] = sigmod(Multy(ws[0], x));
		as[1] = sigmod(Multy(ws[1], x));
		input as_layer2 = { as[0],as[1],1.0 };
		as[2] = sigmod(Multy(as_layer2, ws[2]));
		outs[i] = as[2];
	}

	printf("%0.4f  %0.4f  %0.4f  %0.4f\n", outs[0], outs[1], outs[2], outs[3]);

    return 0;
}

