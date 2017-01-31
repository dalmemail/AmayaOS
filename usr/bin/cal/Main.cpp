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
#include <string.h>
#include <time.h>
#include "cal.h"

#define NOT_ENOUGH_ARGS 0
#define ENOUGH_ARGS 1
#define BAD_YEAR 2
#define BAD_MONTH 3
#define TOO_MUCH_ARGS 4
/* If year is MIN_YEAR and month is not 11 or 12 */
#define BAD_MIN_YEAR_DATE 5

#define MIN_ARGS 2
#define MAX_ARGS 3

#define YEAR_ARG 2
#define YEAR_MONTH_ARG 3

#define MIN_YEAR 1582
#define MAX_YEAR 1000000

#define VERSION "0.2"

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
		if (year < (MIN_YEAR+1) || year > MAX_YEAR) {
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
			if (month < 11) args = BAD_MIN_YEAR_DATE;
		}
		else if (year < MIN_YEAR || year > MAX_YEAR) {
			args = BAD_YEAR;
		}
	}
	if (args != ENOUGH_ARGS) printError(args);
	else {
		/* If we have got just the year */
		if (!month) {
			srandom(time(NULL));
			int random_month = (random() % 12) + 1;
			cal(year,random_month);
			printf("\n[\e[31mWARNING\e[m] If you don't give me a month argument"
			" I will show you a random month\n");
		}
		else cal(year,month);
	}
	return args;
}

void printError(int error_code)
{
	switch (error_code) {
		case BAD_YEAR:
			printf("cal: Year should be between %d and %d\n", MIN_YEAR, MAX_YEAR);
			break;
		case BAD_MONTH:
			printf("cal: Month should be between 1 and 12\n");
			break;
		case BAD_MIN_YEAR_DATE:
			printf("cal: In %d year month should be 11 or 12\n", MIN_YEAR);
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
	char month_cal[256];
	snprintf(month_cal, 256, "   %s %d\nlu ma mi ju vi s%c do\n",
	months_names[month-1], year, 160);
	for (int i = 0; i < weekday; i++) {
		strcat(month_cal, "   ");
	}
	while (day <= month_days) {
		if (day < 10) strcat(month_cal, " ");
		int month_cal_pos = strlen(month_cal);
		snprintf(&month_cal[month_cal_pos], (256-month_cal_pos), "%d ", day++);
		weekday++;
		if (weekday > 6) {
			weekday = 0;
			strcat(month_cal, "\n");
		}
	}
	printf("%s\n", month_cal);
}
