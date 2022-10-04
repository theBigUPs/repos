#include <stdio.h>

//Raw Sharpness Multipliers :

float Purple = 1.50;
float White = 1.30;
float Blue = 1.25;
float Green = 1.125;
float Yellow = 1.0;
float Orange = 0.75;
float Red = 0.50;

//Elemental Sharpness Multipliers :

float lPurple = 1.20;
float lWhite = 1.125;
float lBlue = 1.0625;
float lGreen = 1.0;
float lYellow = 0.75;
float lOrange = 0.50;
float lRed = 0.25;




void calc_raw_dual_blades(float bloat, float sharpness, float affinity, float elemental, float elemental_sharpness )
{
	float elemental_raw = (elemental / 10)*0.70*elemental_sharpness;
	float raw = bloat / 1.4;
	float affinity_raw = raw * ((0.25*affinity) + 1)*sharpness;

	
	printf("%f affinity adjusted raw \n\n%f elemental raw \n\n\n\n",affinity_raw,elemental_raw);
}


//180
//199

int main()
{
	calc_raw_dual_blades(266, Purple, 0.6, 0, lBlue);
}