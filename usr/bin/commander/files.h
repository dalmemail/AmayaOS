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

#define TEXTFILE 0
#define DIRECTORY 1
#define EXECUTABLE 2
#define CHARACTER_DEVICE 3
#define UNKOWNFILE 4

struct dir_entry {
	char file_name[128];
	int fileType;
};

struct dir_entry *get_dir_content(char *path, int n_files);

unsigned int countFiles(char *path);

char *search_parent(char *path);

char *get_last_path(char *path, char *last_dir_selected);

char *makePath(char *path, char *filename, char *file_path);

void inicialice_var(char *var);
