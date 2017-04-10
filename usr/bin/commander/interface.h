/*
 * Copyright (C) 2016, 2017 Daniel Martín
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

void print_entry(struct dir_entry *dir_content[2], struct dir_info dirs[2], int current_dir);

void simple_interface();

void clean_screen();

void print_path(char *first_path, char *second_path);

void print_error(char *error);

void refresh_interface(struct dir_info dirs[2]);

void print_info(struct stat st, char *filename);

void about_commander();

char *get_string(char *message, char *str, int size);

int exit_window();
