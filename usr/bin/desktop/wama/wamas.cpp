/*
 * Copyright (C) 2015 Dan Rulos [amaya@amayaos.com]
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

#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "written.h"
#include "wama.h"
#include "wamas.h"

#define NEW_FILE 0
#define EDIT_FILE 1

void wama()
{
	char tecla = 's';
	setscreenblue();
	setoption();
	setwindow();
	do {
		tecla = getchar();
	} while (tecla != 'V'&& tecla != 'v'&& tecla != 'N'&& tecla != 'n'
		&& tecla != 'S'&& tecla != 's'&& tecla != 'e'&& tecla != 'E');
	if (tecla == 'V'|| tecla == 'v') {
		if (read_wama_file() < 0) {
			error();
		}
	}
	if (tecla == 'N'|| tecla == 'n') {
		if (wama_file(NEW_FILE) < 0) {
			error();
		}
		else {
			save();
		}
	}
	if (tecla == 'E'|| tecla == 'e') {
		if (wama_file(EDIT_FILE) < 0) {
			error();
		}
		else {
			save();
		}
	}
}
