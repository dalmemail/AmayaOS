/*
 * Copyright (C) 2016 Dan Rulos, 2015 Francisco Domínguez
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

#include <stdio.h>
#include <stdlib.h>

#define VERSION "1.3"

#define GOOD_DATE 0
#define BAD_DATE -1

enum days {MONDAY, TUESDAY, WEDNESDAY,
	   THURSDAY, FRIDAY, SATURDAY, SUNDAY};

/* The number of days in a month*/
int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

int checkdate(int day, int month, int year)
{
	int ret = GOOD_DATE;
	if (month > 12 || month < 1 || year < 1582 || day < 1) {
		ret = BAD_DATE;
	}
	if (year == 1582) {
		if (month < 10 || (month == 10 && day < 15)) {
			ret = BAD_DATE;
		}
	}
	if (day > months[month-1]) {
		ret = BAD_DATE;
		if (month == 2 && day == 29) {
			if (year % 4 == 0&& year % 100 != 0) {
				ret = GOOD_DATE;
			}
			if (year % 100 == 0&& year % 400 == 0) {
				ret = GOOD_DATE;
			}
		}
	}
	return ret;
}

int leapdays(int year, int month, int day)
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

int yeardays(int day, int month)
{
	int days = 0;
	for (int i = 1; i < month; i++) {
		days = days + months[i-1];
	}
	days = days + day;
	return days;
}

int calendar(int day, int month, int year)
{
	int ret = 0;
	if ((checkdate(day, month, year)) < 0) {
		printf("FECHA NO VALIDA\n");
		ret = -1;
	}
	else {
		/* date contains the number of days from 15/10/1582 to day/month/year*/
		int date = ((year - 1583) * 365) + 81 + leapdays(year, month, day) + yeardays(day, month);
		switch (date % 7) {
		case MONDAY:
			printf("LUNES\n");
			break;
		case TUESDAY:
			printf("MARTES\n");
			break;
		case WEDNESDAY:
			printf("MIERCOLES\n");
			break;
		case THURSDAY:
			printf("JUEVES\n");
			break;
		case FRIDAY:
			printf("VIERNES\n");
			break;
		case SATURDAY:
			printf("SABADO\n");
			break;
		case SUNDAY:
			printf("DOMINGO\n");
			break;
		}
	}
	return ret;
}

int main(int argc, char **argv)
{
	int ret = EXIT_SUCCESS;
	if (argc != 4) {

		printf("----- CALENDAR %s -----\n", VERSION);
		printf("Uso: %s dia mes a%co\n", argv[0], 164);
		printf("Ejemplo: calendar 14 7 2015\n");
	}
	else {
		ret = calendar(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	}
	return ret;
}
