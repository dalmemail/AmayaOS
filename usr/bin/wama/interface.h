/*
 * Copyright (C) 2016, 2017 Daniel Martín [amaya@amayaos.com]
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

void clean_screen();

void up_bar(char *str1, int sp1, char *str2, int sp2);

void down_bar(int optpos);

void clean_message_line();

void add_message(char *msg);

int get_start_point(int line);

void print_content(char **lines, struct cursor file_cursor, int n_lines);

void get_string(char *str, unsigned int max);
