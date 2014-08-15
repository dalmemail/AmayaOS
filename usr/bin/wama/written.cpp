/*
# Copyright (C) 2014 Team Espartano (AmayaOS).
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>*/

#include <stdio.h>

int written(int argc, char *argv[])
 {
    if(argc<2) 
    {
        printf("\n");
        printf("********************************************************************************\n");
        printf("***************************************  WA+  **********************************\n"); 
        printf("********************************************************************************\n");
        printf("Modulo de escritura 0.1 junglacode \n");
    }
    else
    {
      printf("se guardara en memoria:  %s \n", argv[1]);

    }

   //return 0;
}
