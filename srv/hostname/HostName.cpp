/*
 * Copyright (C) 2012 Felipe Cabrera, 2014 Daniel Martin
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

#include "HostName.h"
#include <stdio.h>
#include <fcntl.h>

Error HostName::initialize()
{
    hostname = "live";
    i = 0;
    return ESUCCESS;
}

Error HostName::read(s8 *buffer, Size size, Size offset)
{
    if(i==1) {
        i=0;
        return 0;
    }
    i++;
    snprintf((char*)buffer, size, "%s", hostname);
    return size;
}

Error HostName::write(s8 *buffer, Size size, Size offset)
{
    hostname = (char*)buffer;
    return size;
}
