/*
 * Copyright (C) 2017 Daniel Martín
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

/*
 * @brief Calculates the day of the week (Monday... Saturday) using a date
 * @param year The year
 * @param month The month
 * @param day The day
 * @return (int) The day of the week (0=Monday, ... 6=Saturday)
 */
int week_day(int year, int month, int day);

/*
 * @brief Check is a year is a leap year or not
 * @param year The year to be checked
 * @return Non-ZERO if 'year' is a leap year, ZERO if else
 */
int leap_year(int year);
