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

#include <Macros.h>
#include "errno.h"

int errno USED = 0;

char * error_map[] USED =
{
    [-ESUCCESS]         = "Success",
    [-E2BIG]            = "Lista de argumentos muy larga",
    [-EACCES]           = "Permiso denegado",
    [-EADDRINUSE]       = "Direccion en uso",
    [-EADDRNOTAVAIL]    = "Direccion no disponible",
    [-EAFNOSUPPORT]     = "Familia de direcciones no soportada",
    [-EAGAIN]           = "Recurso temporalmente no disponible",
    [-EALREADY]         = "Connection already in progress",
    [-EBADF]            = "Bad file descriptor",
    [-EBADMSG]          = "Bad message",
    [-EBUSY]            = "Dispositivo o recurso busy",
    [-ECANCELED]        = "Operacion cancelada",
    [-ECHILD]           = "No hay procesos hijo",
    [-ECONNABORTED]     = "Conexion abortada",
    [-ECONNREFUSED]     = "Connection refused",
    [-ECONNRESET]       = "Conexion reiniciada",
    [-EDEADLK]          = "Resource deadlock would occur",
    [-EDESTADDRREQ]     = "Destination address required",
    [-EDOM]             = "Mathematics argument out of domain of function",
    [-EDQUOT]           = "Reservado",
    [-EEXIST]           = "El fichero ya existe",
    [-EFAULT]           = "Bad address",
    [-EFBIG]            = "Fichero muy largo",
    [-EHOSTUNREACH]     = "Host is unreachable",
    [-EIDRM]            = "Identificador removido",
    [-EILSEQ]           = "Secuencia ilegal de bytes",
    [-EINPROGRESS]      = "Operation in progress",
    [-EINTR]            = "Interrupted function",
    [-EINVAL]           = "Invalid argument",
    [-EIO]              = "Error de E/S",
    [-EISCONN]          = "Socket is connected",
    [-EISDIR]           = "Es un directorio",
    [-ELOOP]            = "Demasiados niveles de enlaces simbolicos",
    [-EMFILE]           = "File descriptor value too large",
    [-EMLINK]           = "Demasiados enlaces",
    [-EMSGSIZE]         = "Mensaje demasiado largo",
    [-EMULTIHOP]        = "Reservado",
    [-ENAMETOOLONG]     = "Nombre de fichero demasiado largo",
    [-ENETDOWN]         = "Network is down",
    [-ENETRESET]        = "Conexion abortada por la red",
    [-ENETUNREACH]      = "Network unreachable",
    [-ENFILE]           = "Demasiados ficheros abiertos en sistema",
    [-ENOBUFS]          = "No buffer space available",
    [-ENODATA]          = "No message is available on the STREAM head read queue",
    [-ENODEV]           = "El dispositivo no existe",
    [-ENOENT]           = "El archivo o directorio no existe",
    [-ENOEXEC]          = "Error en el formato del archivo ejecutable",
    [-ENOLCK]           = "No locks available",
    [-ENOLINK]          = "Reservado",
    [-ENOMEM]           = "No hay suficiente espacio de memoria",
    [-ENOMSG]           = "No message of the desired type",
    [-ENOPROTOOPT]      = "Protocolo no disponible",
    [-ENOSPC]           = "No space left on device",
    [-ENOSR]            = "No hay rocursos STREAM",
    [-ENOSTR]           = "No es un STREAM",
    [-ENOSYS]           = "Funcion no soportada",
    [-ENOTCONN]         = "El socket no esta conectado",
    [-ENOTDIR]          = "No es un directorio",
    [-ENOTEMPTY]        = "El directorio no esta vacio",
    [-ENOTRECOVERABLE]  = "State not recoverable",
    [-ENOTSOCK]         = "No es un socket",
    [-ENOTSUP]          = "Operacion no soportada",
    [-ENOTTY]           = "Inappropriate I/O control operation",
    [-ENXIO]            = "No such device or address",
    [-EOPNOTSUPP]       = "Operation not supported on socket",
    [-EOVERFLOW]        = "Value too large to be stored in data type",
    [-EOWNERDEAD]       = "Previous owner died",
    [-EPERM]            = "Operacion no permitida",
    [-EPIPE]            = "Broken pipe",
    [-EPROTO]           = "Error de protocolo",
    [-EPROTONOSUPPORT]  = "Protocolo no soportado",
    [-EPROTOTYPE]       = "Protocol wrong type for socket",
    [-ERANGE]           = "Resultado demasiado largo",
    [-EROFS]            = "Sistema de archivos de solo lectura",
    [-ESPIPE]           = "Invalid seek",
    [-ESRCH]            = "No existe el proceso",
    [-ESTALE]           = "Reservado",
    [-ETIME]            = "Stream ioctl() timeout",
    [-ETIMEDOUT]        = "Connection timed out",
    [-ETXTBSY]          = "Fichero de texto busy",
    [-EWOULDBLOCK]      = "Operation would block",
    [-EXDEV]            = "Cross-device link"
};
