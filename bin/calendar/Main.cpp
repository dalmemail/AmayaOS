/*
 * Copyright (C) 2014 Dan Rulos.
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

int main(int argc, char **argv)
{
    char d[128];
    char m[128];
    char y[128];
    int dia=0;
    int mes=0;
    int year=0;
    int tyear=0;
    printf("Dia: ");
    gets_s(d, 128);
    dia = atoi(d);
    printf("Mes: ");
    gets_s(m, 128);
    mes = atoi(m);
    printf("A%co: ", 164);
    gets_s(y, 128);
    year = atoi(y);
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
    if (mes == 1) //Sumamos los meses
      cuenta = cuenta + 0;
    if (mes == 2)
      cuenta = cuenta + 31;
    if (mes == 3)
      cuenta = cuenta + 59;
    if (mes == 4)
      cuenta = cuenta + 90;
    if (mes == 5)
      cuenta = cuenta + 120;
    if (mes == 6)
      cuenta = cuenta + 151;
    if (mes == 7)
      cuenta = cuenta + 181;
    if (mes == 8)
      cuenta = cuenta + 212;
    if (mes == 9)
      cuenta = cuenta + 243;
    if (mes == 10)
      cuenta = cuenta + 273;
    if (mes == 11)
      cuenta = cuenta + 304;
    if (mes == 12)
      cuenta = cuenta + 334;
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
    //cout << cuenta<< endl; //Código del día....
    int valor;
    valor = cuenta % 7;
    if (valor == 0) {
      printf("LUNES\r\n");
      return 0;
    }
    if (valor == 1) {
      printf("MARTES\r\n");
      return 0;
    }
    if (valor == 2) {
      printf("MIERCOLES\r\n");
      return 0;
    }
    if (valor == 3) {
      printf("JUEVES\r\n");
      return 0;
    }
    if (valor == 4) {
      printf("VIERNES\r\n");
      return 0;
    }
    if (valor == 5) {
      printf("SABADO\r\n");
      return 0;
    }
    if (valor == 6) {
      printf("DOMINGO\r\n");
      return 0;
    }
}
