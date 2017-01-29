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

static int leapdays(int year, int month, int day)
{
	int days = 0;
	for (int i = 1582; i <= year; i++) {
		if (i % 4 == 0&& i % 100 != 0) {
			if (i == year && month < 3) {
				days--;
			}
			days++;
		}
		if (i % 100 == 0&& i % 400 == 0) {
			if (i == year && month < 3) {
				days--;
			}
			days++;
		}
	}
	return days;
}

static int yeardays(int day, int month)
{
	int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int days = 0;
	for (int i = 1; i < month; i++) {
		days = days + months[i-1];
	}
	days = days + day;
	return days;
}

int week_day(int year, int month, int day)
{
	int days = ((year - 1583) * 365)+81+leapdays(year, month, day) + yeardays(day, month);
	return (days % 7);
}

#define LEAP_YEAR 1
#define NOT_LEAP_YEAR 0

int leap_year(int year)
{
	int ret = NOT_LEAP_YEAR;
	if ((year % 4 == 0&& year % 100 != 0) || (year % 100 == 0&& year % 400 == 0)) {
		ret = LEAP_YEAR;
	}
	return ret;
}
