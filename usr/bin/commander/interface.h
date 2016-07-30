/*
 * Copyright (C) 2016 Dan Rulos
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

void print_entry(struct dir_entry *dir_content, int cursor, int n_files);

void simple_interface();

void clean_screen();

void print_path(char *path);

void print_error(char *error);

void refresh_interface(char *path);

void print_info(struct stat st, char *path, char *filename);

void about_commander();

char *get_string(char *message, char *str, int size);
