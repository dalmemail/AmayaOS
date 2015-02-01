/*
 * Copyright (C) 2014 Dan Rulos
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

/* This software has been edited to support the FreeNOS time */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <files.h>

int main(int argc, char **argv)
{
    file *f = new file();
    f->setpath("/dev/time");
    f->f_open(O_RDONLY);
    char *ch = f->readAll();
    f->f_close();
    int fecha_s = atoi(ch);
    //int fecha_s = 1420453541;
    int year=0;
    int month=0;
    int day=0;
    int hour=0;
    int min=0;
    int second=0;
    min = fecha_s / 60;
    second = fecha_s % 60;
    hour = min / 60;
    min = min % 60;
    day = hour / 24;
    hour = hour % 24;
    year = day / 365;
    year = year + 1970;
    day = day % 365;
    //¿Es bisiesto el año?
    int cuenta=0;
    for (int year_for=1970; year_for <= year; year_for++) {
       if (year_for % 4 == 0&& year_for % 100 != 0) {
        cuenta++;
      }
      if (year_for % 4 != 0&& year_for % 100 == 0&& year_for % 400 == 0) {
        cuenta++;
      }
    }
    int feb=0;
    if (year % 4 == 0&& year % 100 != 0) {
      feb++;
    }
    if (year % 100 == 0&& year % 400 == 0) {
      feb++;
    }
    //Obtener los meses.
    if (day >= 1&& day <= 31) {
       month = 1;
    }
    if (day >= 32&& day <= 59+feb) {
       month = 2;
       day=day-31;
    }
    if (day >= 60+feb&& day <= 90+feb) {
       month = 3;
       day=day-(59+feb);
    }
    if (day >= 91+feb&& day <= 120+feb) {
       month = 4;
       day=day-(90+feb);
    }
    if (day >= 121+feb&& day <= 151+feb) {
       month = 5;
       day=day-(120+feb);
    }
    if (day >= 152+feb&& day <= 181+feb) {
       month = 6;
       day=day-(151+feb);
    }
    if (day >= 182+feb&& day <= 212+feb) {
       month = 7;
       day=day-(181+feb);
    }
    if (day >= 213+feb&& day <= 243+feb) {
       month = 8;
       day=day-(212+feb);
    }
    if (day >= 244+feb&& day <= 273+feb) {
       month = 9;
       day=day-(243+feb);
    }
    if (day >= 274+feb&& day <= 304+feb) {
       month = 10;
       day=day-(273+feb);
    }
    if (day >= 305+feb&& day <= 334+feb) {
       month = 11;
       day=day-(304+feb);
    }
    if (day >= 335+feb&& day <= 365+feb) {
       month = 12;
       day=day-(334+feb);
    }
    day=day-cuenta;

    printf("%d:%d:%d %d/%d/%d\r\n", hour, min, second, day, month, year-6);
    return 0;
}
