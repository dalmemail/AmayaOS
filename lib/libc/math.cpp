/*
 * Copyright (C) 2015 Alvaro Stagg [alvarostagg@openmailbox.org], 2016 Dan Rulos
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "math.h"

double pow(double base, double potencia)
{
	if(potencia == 0.0 && base != 0.0)
		return 1.0;
	else if(potencia == 0.0 && base == 0.0)
		return 0.0;

	double m = 1.0;

	for(int i = 1; i <= potencia; i++)
	{
  	m *= base;
	}

  return m;
}

float pow(float base, float potencia)
{
	if(potencia == 0.0 && base != 0.0)
		return 1.0;
	else if(potencia == 0.0 && base == 0.0)
		return 0.0;

	float m = 1.0;

	for (int i = 1;i <= potencia; i++)
	{
  	m *= base;
	}

	return m;
}

long double pow(long double base, long double potencia)
{
	if(potencia == 0.0 && base != 0.0)
		return 1.0;
	else if(potencia == 0.0 && base == 0.0)
		return 0.0;

	long double m = 1.0;

	for(int i = 1; i <= potencia; i++)
	{
  	m *= base;
	}

	return m;
}

double pow(double base, int potencia)
{
	if(potencia == 0 && base != 0)
		return 1;
	else if(potencia == 0 && base == 0)
		return 0;

	double m = 1.0;

  for(int i = 1; i <= potencia; i++)
  {
  	m *= base;
	}

	return m;
}

long double pow(long double base, int potencia)
{
	if(potencia == 0 && base != 0)
		return 1;
	else if(potencia == 0 && base == 0)
		return 0;

	long double m = 1.0;

  for(int i = 1; i <= potencia; i++)
  {
  	m *= base;
	}

	return m;
}

double sqrt(double base)
{
	double c = 0, mod = 1;

	if(base <= 0)
	{
		return 0;
	}

	int i = 0;
	do {
		c += mod;
		if(c * c > base)
		{
			c -= mod;
			mod /= 10;
		}
		if (mod <= 0.000001) {
			i++;
		}
	} while (c * c != base && i <= 10);

	return c;
}

float sqrt(float base)
{
	float c = 0, mod = 1;

	if(base <= 0)
	{
		return 0;
	}

	for(int i = 0; i < (50+base); c += mod, i++)
	{
		if(c * c > base)
		{
			c -= mod;
			mod /= 10;
		}
	}

	return c;
}

long double sqrt(long double base)
{
	long double c = 0, mod = 1;

	if(base <= 0)
	{
		return 0;
	}

	for(int i = 0; i < (50+base); c += mod, i++)
	{
		if(c * c > base)
		{
			c -= mod;
			mod /= 10;
		}
	}

	return c;
}

double cbrt(double base)
{
    double c = 0, mod = 1;

    if(base <= 0)
    {
    	return 0;
    }

    for(int i = 0; i < base; c += mod, i++)
    {
			if(c * c * c > base)
      {
      	c -= mod;
        mod /= 10;
      }
    }

    return c;
}

float cbrt(float base)
{
    float c = 0, mod = 1;

    if(base <= 0)
    {
    	return 0;
    }

    for(int i = 0; i < base; c += mod, i++)
    {
    	if(c * c * c > base)
      {
      	c -= mod;
        mod /= 10;
      }
    }

    return c;
}

long double cbrt(long double base)
{
	long double c = 0, mod = 1;

	if(base <= 0)
	{
		return 0;
	}

	for(int i = 0; i < base; c += mod, i++)
	{
		if(c * c * c > base)
			{
					c -= mod;
					mod /= 10;
			}
	}

	return c;
}

double hypot(double x, double y)
{
	return pow(x, 2) + pow(y, 2);
}

float hypot(float x, float y)
{
	return pow(x, 2) + pow(y, 2);
}

long double hypot(long double x, long double y)
{
	return pow(x, 2) + pow(y, 2);
}

double exp2(double x)
{
	return pow(2, x);
}

float exp2(float x)
{
	return pow(2, x);
}

long double exp2(long double x)
{
	return pow(2, x);
}

double log10(double x)
{
	int i = 0;

	if(x < 0) /* ERROR */
		return -1;
	else
	{
		double sn = 0;

		while(sn != x)
		{
			if(i >= (int)x)
				break;

			sn = pow(10.0, i);
			i++;
		}
	}

	return i - 1;
}

float log10(float x)
{
	int i = 0;

	if(x < 0) /* ERROR */
		return -1;
	else
	{
		float sn = 0;

		while(sn != x)
		{
			if(i >= (int)x)
				break;

			sn = pow(10.0, i);
			i++;
		}
	}

	return i - 1;
}

long double log10(long double x)
{
	int i = 0;

	if(x < 0) /* ERROR */
		return -1;
	else
	{
		long double sn = 0;

		while(sn != x)
		{
			if(i >= (int)x)
				break;

			sn = pow(10.0, i);
			i++;
		}
	}

	return i - 1;
}


double sin(double x)
{
	return x - ((x * x) / (1 * 2 * 3));
}

float sin(float x)
{
	return x - ((x * x) / (1 * 2 * 3));
}

long double sin(long double x)
{
	return x - ((x * x) / (1 * 2 * 3));
}

double abs(double x)
{
	if(x < 0)
		return (x - x) -(x);
	else
		return x;
}

float abs(float x)
{
	if(x < 0)
		return (x - x) -(x);
	else
		return x;
}

long double abs(long double x)
{
	if(x < 0)
		return (x - x) -(x);
	else
		return x;
}

double fabs(double x)
{
	if(x < 0)
		return (x - x) -(x);
	else
		return x;
}

float fabs(float x)
{
	if(x < 0)
		return (x - x) -(x);
	else
		return x;
}

long double fabs(long double x)
{
	if(x < 0)
		return (x - x) -(x);
	else
		return x;
}

double fma(double x, double y, double z)
{
	return (x * y) + z;
}

float fmaf(float x, float y, float z)
{
	return (x * y) + z;
}

long double fmal(long double x, long double y, long double z)
{
	return (x * y) + z;
}

double fmax(double x, double y)
{
	if(x > y)
		return x;
	else
		return y;
}

float fmaxf(float x, float y)
{
	if(x > y)
		return x;
	else
		return y;
}

long double fmaxl(long double x, long double y)
{
	if(x > y)
		return x;
	else
		return y;
}

double fmin(double x, double y)
{
	if(x < y)
		return x;
	else
		return y;
}

float fminf(float x, float y)
{
	if(x < y)
		return x;
	else
		return y;
}

long double fminl(long double x, long double y)
{
	if(x < y)
		return x;
	else
		return y;
}

double modf(double x, double* intpart)
{
	double dec_part = x - (int)x;
	double _intpart = intpart - &dec_part;

	return dec_part;
}

float modf(float x, float* intpart)
{
	float dec_part = x - (int)x;
	float _intpart = intpart - &dec_part;

	return dec_part;
}

long double modf(long double x, long double* intpart)
{
	long double dec_part = x - (int)x;
	long double _intpart = intpart - &dec_part;

	return dec_part;
}

double floor(double x)
{
	double rgv;

	if(x < 0)
		rgv = (int)x - 1;
	else
		rgv = (int)x;

	return rgv;
}

float floor(float x)
{
	float rgv;

	if(x < 0)
		rgv = (int)x - 1;
	else
		rgv = (int)x;

	return rgv;
}

long double floor(long double x)
{
	long double rgv;

	if(x < 0)
		rgv = (int)x - 1;
	else
		rgv = (int)x;

	return rgv;
}
