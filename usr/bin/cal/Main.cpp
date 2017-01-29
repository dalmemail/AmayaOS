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

#include <stdio.h>
#include <stdlib.h>
#include "cal.h"

#define NOT_ENOUGH_ARGS 0
#define ENOUGH_ARGS 1
#define BAD_YEAR 2
#define BAD_MONTH 3
#define TOO_MUCH_ARGS 4

#define MIN_ARGS 2
#define MAX_ARGS 3

#define YEAR_ARG 2
#define YEAR_MONTH_ARG 3

#define MIN_YEAR 1582

#define VERSION "0.1"

int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
char *months_names[12] = {"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto",
"Septiembre","Octubre","Noviembre","Diciembre"};

void printError(int error_code);
void usage();
void cal(int year, int month);

int main(int argc, char **argv)
{
	int args = 1;
	int year = 0;
	int month = 0;
	if (argc < MIN_ARGS) {
		args = NOT_ENOUGH_ARGS;
	}
	else if (argc > MAX_ARGS) {
		args = TOO_MUCH_ARGS;
	}
	else if (argc == YEAR_ARG) {
		year = atoi(argv[1]);
		if (year < (MIN_YEAR+1)) {
			args = BAD_YEAR;
		}
	}
	else if (argc == YEAR_MONTH_ARG) {
		year = atoi(argv[2]);
		month = atoi(argv[1]);
		if (month < 1 || month > 12) {
			args = BAD_MONTH;
		}
		else if (year == MIN_YEAR) {
			if (month < 10) args = BAD_MONTH;
		}
		else if (year < MIN_YEAR) {
			args = BAD_YEAR;
		}
	}
	if (args != ENOUGH_ARGS) printError(args);
	else {
		/* If we have got just the year */
		if (month == 0) {
			for (int i = 1; i <= 12; i++) {
				cal(year,i);
			}
		}
		else cal(year,month);
	}
	return args;
}

void printError(int error_code)
{
	switch (error_code) {
		case BAD_YEAR:
			printf("cal: Year should be between %d and infinity\n", (MIN_YEAR+1));
			break;
		case BAD_MONTH:
			printf("cal: Month should be between 1 and 12\n");
			break;
		case NOT_ENOUGH_ARGS:
		case TOO_MUCH_ARGS:
			usage();
			break;
	}
}

void usage()
{
	printf("Cal v%s is a free calendar software for your system\n", VERSION);
	printf(" usage: cal [YEAR]\n\tcal [MONTH] [YEAR]\n");
}

void cal(int year, int month)
{
	int day = 1;
	int weekday = week_day(year,month,1);
	int month_days = months[month-1];
	if (month == 2 && leap_year(year)) month_days++;
	//char month_cal[256];
	/*sn*/printf(/*month_cal, 256, */"   %s %d\nlu ma mi ju vi s%c do\n",
	months_names[month-1], year, 160);
	for (int i = 0; i < weekday; i++) {
		printf/*strcat*/(/*month_cal, */"   ");
	}
	while (day <= month_days) {
		if (day < 10) printf/*strcat*/(/*month_cal, */" ");
		/*sn*/printf(/*month_cal, 256, */"%d ", day++);
		weekday++;
		if (weekday > 6) {
			weekday = 0;
			printf/*strcat*/(/*month_cal,*/ "\n");
		}
	}
	printf("\n\n");
	//printf("%s\n", month_cal);
}
