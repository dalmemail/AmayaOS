/*
 * Copyright (C) 2016 Dan Rulos [amaya@amayaos.com]
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

#ifndef WAMA_H
#define WAMA_H

#define READ_MODE 0
#define WRITE_MODE 1

void setwindow();

void setscreenblue();

void setoption();

void clean_screen();

void error();

void save();

int checkWamaCommand(char *line);

int linecounter(char *c);

char *read_file(char *path);

int get_size(char *path);

char *edit_lines(char *str, size_t size, char *line_to_edit);

int line_navigator(char *path, int mode);

#endif
