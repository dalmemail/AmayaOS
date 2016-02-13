/*
 * Copyright (C) 2016 Dan Rulos.
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

#ifndef _CALCULATOR_H
#define _CALCULATOR_H

/**
 * @brief Convert a double to a string.
 * @param r
 * @param input Double value to convert.
 * @return Nothing (void).
 */
void ftoa(char r[16], double input);

/**
 * @brief Do operations (+, -, *, /, %).
 * @param num1 First Number (double).
 * @param operation Char value to select the type of operation.
 * @param num2 Second Number (double).
 * @return Return the operation result.
 */
double calculator(double num1, char operation, double num2);

#endif
