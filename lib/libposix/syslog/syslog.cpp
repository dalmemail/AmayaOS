/*
 * Copyright (C) 2009 Niek Linnenbank
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

#include "POSIXSupport.h"
#include <TerminalCodes.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "syslog.h"
#include "unistd.h"

void syslog(int priority, const char *message, ...)
{
    char line[256], input[256];
    char *priorityStr;
    va_list args;
    
    switch (priority) {
        case LOG_EMERG:
            priorityStr = RED;
            strcat(priorityStr,"EMERGENCIA");
            break;
        case LOG_CRIT:
            priorityStr = RED;
            strcat(priorityStr,"CRITICO");
            break;
        case LOG_ERR:
            priorityStr = RED;
            strcat(priorityStr,"ERROR");
            break;
        case LOG_WARNING:
            priorityStr = YELLOW;
            strcat(priorityStr,"EMERGENCIA");
            break;
        case LOG_NOTICE:
            priorityStr = "AVISO";
            break;
        case LOG_INFO:
            priorityStr = "INFO";
            break;
        case LOG_DEBUG:
            priorityStr = "DEPURAR";
            break;
    }
    
    /* Format the message. */
    va_start(args, message);
    vsnprintf(input, sizeof(input), message, args);
    va_end(args);
    
    /* Create final message. */
    snprintf(line, sizeof(line), "%s %s[%u]: %s" WHITE "\n",
         priorityStr, procs[getpid()]->command, getpid(), input);
	     
    /* Write it to the log device. */
    write(logFile, line, strlen(line));
}
