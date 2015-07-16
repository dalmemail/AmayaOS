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

#include <stdlib.h>
#include <files.h>
#include <sys/stat.h>
#include "uptime_path.h"
#include "uptime_server.h"

int uptime_server()
{
     file *f = new file();
     f->setpath(TIME);
     f->f_open(O_RDONLY);
     char *ch = f->readAll();
     f->f_close();
     int fd;
     touch(UPTIME_, S_IWUSR | S_IRUSR);
     if ((fd = open(UPTIME_, O_WRONLY)) < 0) {
         return -1;
     }
     write(fd, ch, strlen(ch));
     return 0;
}
