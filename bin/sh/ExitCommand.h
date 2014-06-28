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

#ifndef __SH_EXITCOMMAND
#define __SH_EXITCOMMAND

#include <Factory.h>
#include <Types.h>
#include "ShellCommand.h"

/**
 * Salir de la consola.
 */
class ExitCommand : public ShellCommand, public Factory<ExitCommand>
{
    public:
    
	/**
	 * Constructor.
	 */
	ExitCommand() : ShellCommand("exit", 0)
	{
	}

	/**
	 * Obtiene la ayuda para este comando.
	 * @return Puntero de caracteres que describe lo que el comando hace.
	 */
	const char * help()
	{
	    return "Salir de la consola";
	}
    
	/**
	 * Ejecuta el comando.
	 * @param nparams Numero de parametros.
	 * @param params Arreglo de parametros.
	 * @return Codigo de error o cero al finalizar.
	 */
	int execute(Size nparams, char **params);
};

#endif /* __SH_EXITCOMMAND */
