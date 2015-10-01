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
 
#ifndef AMAYAMATH_H
#define AMAYAMATH_H

#define M_PI 3.14159265358979323846 /* PI */
#define PI   3.14159265             /* PI min */

/* Funciones de potenciación */
int pow(int base, int potencia);
double pow(double base, double potencia);
float pow(float base, float potencia);

int sqrt(int base);
double sqrt(double base);
float sqrt(float base);

int cbrt(int base);
double cbrt(double base);
float cbrt(float base);

int hypot(int x, int y);
double hypot(double x, double y);
float hypot(float x, float y);
/* Fin de funciones de potenciación */

unsigned rand();

#endif
