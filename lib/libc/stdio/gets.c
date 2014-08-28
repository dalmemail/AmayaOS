/*
 * Copyright (C) 2012 Felipe Cabrera
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

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

char *gets(char *str)
{
    char line[1024];
    Size total = 0;
    Size point = 0;

    /* Leemos una linea. */
    while (total < sizeof(line)) {
        /* Leemos un caracter. */
        read(0, line + point, 1);

        /* Procesamos el caracter. */
        switch (line[point]) {
            case '\r':
            case '\n':
                printf("\r\n");
                line[total] = ZERO;
                strlcpy(str, line, sizeof(line));
                return str;

            case '\b':
                if (total > 0) {
                    line[--total] = ZERO;
                    point--;
                    printf("\b \b");
                }
                break;
                
            case '\a':
                /*
                if(point > 0) {
                    printf("\b");
                    point--;
                }
                */
                break;
                
            default:
                printf("%c", line[point]);
                point++;
                total++;
                break;
        }
    }
    
    line[total] = ZERO;
    
    return NULL;
}