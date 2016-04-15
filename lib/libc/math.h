/*
 * Copyright (C) 2015 Alvaro Stagg [alvarostagg@openmailbox.org]
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

#ifndef AMAYAMATH_H
#define AMAYAMATH_H

/* algunas constantes que pueden ser utiles */
#define M_PI      3.14159265358979323846  /* PI */
#define PI        3.14159265              /* PI min */
#define M_PI_2    1.57079632679489661923  /* pi / 2 */
#define M_PI_4    0.78539816339744830962  /* pi / 4 */
#define M_1_PI    0.31830988618379067154  /*  1 / PI */
#define M_2_PI    0.63661977236758134308  /*  2 / PI */

/* Funciones de potenciación */
double pow(double base, double potencia);
float pow(float base, float potencia);
long double pow(long double base, long double potencia);
double pow(double base, int potencia);
long double pow(long double base, int potencia);

double sqrt(double base);
float sqrt(float base);
long double sqrt(long double base);

double cbrt(double base);
float cbrt(float base);
long double cbrt(long double base);

double hypot(double x, double y);
float hypot(float x, float y);
long double hypot(long double x, long double y);

double exp2(double x);
float exp2(float x);
long double exp2(long double x);
/* Fin de funciones de potenciación */

/* trigonometría
double cos(double x);
float cos(float x);
long double cos(long double x);

double sin(double x);
float sin(float x);
long double sin(long double x);

*** AÚN NO ESTA EN USO ***
***  STILL NOT IN USE  ***

 fin trigonometría */

/* Logaritmos */
/*double log(double x);
float log(float x);
long double log(long double x);*/

double log10(double x);
float log10(float x);
long double log10(long double x);
/* Fin logaritmos */

/* Otras */
double abs(double x);
float abs(float x);
long double abs(long double x);

double fabs(double x);
float fabs(float x);
long double fabs(long double x);

double fma(double x, double y, double z);
float fmaf(float x, float y, float z);
long double fmal(long double x, long double y, long double z);

double fmax(double x, double y);
float fmaxf(float x, float y);
long double fmaxl(long double x, long double y);

double fmin(double x, double y);
float fminf(float x, float y);
long double fminl(long double x, long double y);

double modf(double x, double* intpart);
float modf(float x, float* intpart);
long double modf(long double x, long double* intpart);

double floor(double x);
float floor(float x);
long double floor(long double x);
/* Fin otras */

#endif /* AmayaMath.h */
