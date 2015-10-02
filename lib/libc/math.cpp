/*
 * Copyright (C) 2015 Alvaro Stagg
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

int pow(int base, int potencia)
{
	int m = 1;

	for (int i = 1; i <= potencia; i++)
	{
		m *= base;
	}

	return m;
}

double pow(double base, double potencia)
{
	double m = 1;

  	for(int i = 1; i <= potencia; i++)
  	{
    		m *= base;
  	}

  	return m;
}

int sqrt(int base)
{
	int c = 0, mod = 1;
	
	if(base <= 0)
	{
		return 0;
	}
	
	for(int i = 0; i < base; c += mod, i++)
	{
		if(c * c > base)
		{
			c -= mod;
			mod /= 10;	
		}
	}
	
	return c;
}

double sqrt(double base)
{
    double c = 0, mod = 1;
	
	if(base <= 0)
	{
		return 0;
	}
	
	for(int i = 0; i < base; c += mod, i++)
	{
		if(c * c > base)
		{
			c -= mod;
			mod /= 10;	
		}
	}
	
	return c;
	
}

int cbrt(int base)
{
    int c = 0, mod = 1;
  
    if(base <= 0)
    {
    	return 0;
    }
  
    for(int i = 0; i < 50; c += mod, i++)
    {
    	if(c * c * c > base)
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
  
    for(int i = 0; i < 50; c += mod, i++)
    {
    	if(c * c * c > base)
        {
          	c -= mod;
            mod /= 10;
        }
    }
  
    return c;	
}

int hypot(int x, int y)
{
  int rs;

  rs = pow(x, 2) + pow(y, 2);
  
  return rs;
}

double hypot(double x, double y)
{
  double rs;

  rs = pow(x, 2.0) + pow(y, 2.0);

  return rs;
}
