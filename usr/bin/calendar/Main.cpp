/*
 * Copyright (C) 2014 Dan Rulos, 2015 Francisco Domínguez
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

#define VERSION "1.1"
#define AUTHOR "Francisco Dominguez"

int main(int argc, char **argv)
{

	if (!argv[1] || (strcmp(argv[1], "--help"))==0) {

		printf("----- CALENDAR %s by %s -----\n", VERSION, AUTHOR);
		printf("Uso: %s dia mes a%co\n", argv[0], 164);
		printf("Ejemplo: calendar 14 7 2015\n");
		return 0;

	}
    int dia = atoi(argv[1]);
    int mes = atoi(argv[2]);
    int year = atoi(argv[3]);
    if (year < 1582) {
      printf("FECHA NO VALIDA\r\n");
      return -1;
    }
    if (year == 1582) {
      if (mes < 10) {
        printf("FECHA NO VALIDA\r\n");
        return -1;
      }
      if (mes == 10) {
        if (dia < 15) {
          printf("FECHA NO VALIDA\r\n");
          return -1;
        }
      }
    }
    if (mes > 12) {
      printf("FECHA NO VALIDA\r\n");
      return -1;
    }
    if (dia == 0) {
      printf("FECHA NO VALIDA\r\n");
      return -1;
    }
    if (dia > 31) {
      printf("FECHA NO VALIDA\r\n");
      return -1;
    }
    if (mes == 0) {
      printf("FECHA NO VALIDA\r\n");
      return -1;
    }
    if (mes == 4||mes == 6||mes == 9||mes == 11) {
      if (dia > 30) {
        printf("FECHA NO VALIDA\r\n");
        return -1;
      }
    }
    if (mes == 2) {
      if (dia > 29) {
        printf("FECHA NO VALIDA\r\n");
        return -1;
      }
      if (dia == 29) {
        if (year % 4 == 0&& year % 100 != 0) {
          //cout << "OK..."<< endl;
        }
        if (year % 100 == 0&& year % 400 == 0) {
          //cout << "OK..."<< endl;
        }
        else {
          printf("FECHA NO VALIDA\r\n");
          return -1;
        }
      }
    }
    int cuenta=0;
    cuenta = year - 1582;
    cuenta = cuenta * 365;
    cuenta = cuenta + 81;
    cuenta = cuenta - 365;
    if (year == 1582) {
      cuenta = cuenta - 273;
    }
	switch (mes) {
    case 1: //Sumamos los meses
      cuenta = cuenta + 0;
	  break;;
    case 2:
      cuenta = cuenta + 31;
	  break;;
    case 3:
      cuenta = cuenta + 59;
	  break;;
    case 4:
      cuenta = cuenta + 90;
	  break;;
    case 5:
      cuenta = cuenta + 120;
	  break;;
    case 6:
      cuenta = cuenta + 151;
	  break;;
    case 7:
      cuenta = cuenta + 181;
	  break;;
    case 8:
      cuenta = cuenta + 212;
	  break;;
    case 9:
      cuenta = cuenta + 243;
	  break;;
    case 10:
      cuenta = cuenta + 273;
	  break;;
    case 11:
      cuenta = cuenta + 304;
	  break;;
    case 12:
      cuenta = cuenta + 334;
	  break;;
	}
    cuenta = cuenta + dia; //sumamos los dias
    int i;
    for (i=1582; i <= year; i++) {
      if (i % 4 == 0&& i % 100 != 0) {
        cuenta = cuenta + 1;
      }
      if (i % 100 == 0&& i % 400 == 0) {
        cuenta = cuenta + 1;
      }
    }
    if (year % 4 == 0) {
      if (year % 4 == 0&& year % 100 != 0) {
        if (mes <= 2) {
          cuenta = cuenta - 1;
        }
      }
      if (year % 100 == 0&& year % 400 == 0) {
        if (mes <= 2) {
          cuenta = cuenta - 1;
        }
      }
    }
    if (year == 1582) {
      cuenta = cuenta - 11;
      cuenta = cuenta + 284;
    }
    int valor;
    valor = cuenta % 7;

    switch (valor) {
    case 0:
      printf("LUNES\r\n");
      return 0;

    case 1:
      printf("MARTES\r\n");
      return 0;
    case 2:
      printf("MIERCOLES\r\n");
      return 0;
    case 3:
      printf("JUEVES\r\n");
      return 0;
    case 4:
      printf("VIERNES\r\n");
      return 0;
    case 5:
      printf("SABADO\r\n");
      return 0;
    case 6:
      printf("DOMINGO\r\n");
      return 0;
    }
}
