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

#include <API/IPCMessage.h>
#include <FileSystemMessage.h>
#include <Config.h>
#include "POSIXSupport.h"
#include <errno.h>
#include "sys/stat.h"

int touch(const char *path, mode_t mode) /* Creamos touch */
{
    FileSystemMessage msg;
    ProcessID mnt = findMount(path);

    /* ¿Como es el archivo?. */
    msg.action = CreateFile;    /* ¿Que hacemos con el archivo? */
    msg.buffer = (char *) path;
    msg.mode   = mode;
    msg.filetype = RegularFile; /* Tipo de archivo : txt, directorio, etc */
    
    /* Le preguntamos al OS si permite crearlo. */
    if (mnt)
    {
	IPCMessage(mnt, SendReceive, &msg, sizeof(msg));

	/* ¿Error?. */
	errno = msg.result;
    }
    else
	errno = ENOENT;
    
    /* Finalizando..... */
    return msg.result == ESUCCESS ? 0 : -1;
}
