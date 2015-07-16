/*
 * Copyright (C) 2015 Dan Rulos
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

#include <files.h>
#include <stdlib.h>
#include <stdio.h>
#include "uptime_path.h"
#include "uptime.h"

int uptime()
{
     /* Leemos los archivos con los datos del tiempo */
     file *f1 = new file();
     f1->setpath(TIME);
     f1->f_open(O_RDONLY);
     char *time = f1->readAll();
     f1->f_close();
     /* Convertimos a INT */
     int t = atoi(time);
     file *f2 = new file();
     f2->setpath(UPTIME_);
     f2->f_open(O_RDONLY);
     char *uptim = f2->readAll();
     f2->f_close();
     /* Convertimos a INT */
     int p = atoi(uptim);
     /* calculamos el uptime real */
     int uptime = t - p;
     /* calculamos las unidades de tiempo */
     int minutos = uptime / 60;
     int segundos = uptime % 60;
     int horas = minutos / 60;
     minutos = minutos % 60;
     int dias = horas / 24;
     horas = horas % 24;
     printf("up %d day(s) %d:%d:%d\n", dias, horas, minutos, segundos);
     return 0;
}
