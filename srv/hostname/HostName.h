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

#ifndef __LOG_SYSTEMLOG_H
#define __LOG_SYSTEMLOG_H

/**
 * @defgroup systemlog SystemLog (Generic Logging Device)
 * @{  
 */

#include <Device.h>
#include <Types.h>
#include <Macros.h>
#include <Error.h>

/**
 * Logs output and debug messages.
 */
class HostName : public Device
{
public:   
	Error initialize();
	Error read(s8 *buffer, Size size, Size offset);
    Error write(s8 *buffer, Size size, Size offset);
    
private:
    char *hostname;
    int i;
};

/**
 * @}
 */

#endif /* __LOG_SYSTEMLOG_H */
