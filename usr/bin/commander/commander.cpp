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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "commander.h"
#include "files.h"
#include "interface.h"

#define EXIT_KEY 'e'
#define UP_KEY 'w'
#define DOWN_KEY 's'
#define INFO_KEY 'i'
#define ABOUT_KEY 'a'
#define CREATE_FILE_KEY 'f'
#define CREATE_DIR_KEY 'd'
#define MOVE_KEY 'm'
#define COPY_KEY 'c'
#define PASTE_KEY 'p'
#define CHANGE_WORKSPACE_KEY ' '

#define MAX_DIRS 2

#define RUNNING 1
#define EXITING 0

struct dir_info dirs[2];

void commander(char *path, char *cwd)
{
	int status = RUNNING;
	int current_dir = 0;
	int error_code = 0;
	char key;
	struct dir_entry *dir_content[MAX_DIRS];
	strcpy(dirs[0].path, path);
	dirs[0].cursor_position = 0;
	strcpy(dirs[1].path, cwd);
	dirs[1].cursor_position = 0;
	refresh_interface(dirs);
	if ((error_code = checkDir(dirs[0].path)) != 0 ||
	(error_code = checkDir(dirs[1].path)) != 0) {
		print_error(strerror(error_code));	
	}
	else print_error("Welcome to Amaya File Commander");
	dirs[0].n_files = countFiles(dirs[0].path);
	dir_content[0] = get_dir_content(dirs[0].path, dirs[0].n_files);
	dirs[1].n_files = countFiles(dirs[1].path);
	dir_content[1] = get_dir_content(dirs[1].path, dirs[1].n_files);
	int cursor_position = dirs[current_dir].cursor_position;
	int n_files = dirs[current_dir].n_files;
	char *current_path = &dirs[current_dir].path[0];
	char copy_path[256];
	char *paste_filename;
	while (status != EXITING) {
		dirs[current_dir].cursor_position = cursor_position;
		dirs[current_dir].n_files = n_files;
		if (n_files > 19) {
			refresh_interface(dirs);}
			/*print_entry(dir_content, dirs, current_dir);
			simple_interface();
		}
		else */print_entry(dir_content, dirs, current_dir);
		key = getchar();
		if (key == UP_KEY && cursor_position > 0) {
			cursor_position--;
		}
		else if (key == EXIT_KEY) {
			if ((status = exit_window())) refresh_interface(dirs);
		}
		else if (key == CHANGE_WORKSPACE_KEY) {
			dirs[current_dir].n_files = n_files;
			dirs[current_dir].cursor_position = cursor_position;
			current_dir = (!current_dir) ? 1 : 0;
			n_files = dirs[current_dir].n_files;
			cursor_position = dirs[current_dir].cursor_position;
			current_path = &dirs[current_dir].path[0];
			refresh_interface(dirs);
		}
		else if (key == DOWN_KEY && (cursor_position+1) < n_files) {
			cursor_position++;
		}
		else if (key == '\n') {
			if (dir_content[current_dir][cursor_position].fileType == DIRECTORY) {
				if (strcmp(dir_content[current_dir][cursor_position].file_name, "..") != 0) {
					char *entry = &dir_content[current_dir][cursor_position].file_name[0];
					if (strcmp(current_path, "/") != 0) {
						strcat(current_path, "/");
					}
					strcat(current_path, entry);
					int result;
					if ((result = checkDir(current_path)) == 0) {
						free(dir_content[current_dir]);
						n_files = countFiles(current_path);
						dir_content[current_dir] = get_dir_content(current_path, n_files);
						refresh_interface(dirs);
						cursor_position = 0;
						/* We copy new values into structure */
						dirs[current_dir].n_files = n_files;
						dirs[current_dir].cursor_position = cursor_position;
					}
					else {
						get_last_path(current_path, entry);
						print_error(strerror(result));
					}
				}
				else if (strcmp(current_path, "/") != 0) {
					char last_path[strlen(current_path)];
					strcpy(last_path, current_path);
					search_parent(current_path);
					int result;
					if ((result = checkDir(current_path)) == 0) {
						free(dir_content);
						n_files = countFiles(current_path);
						dir_content[current_dir] = get_dir_content(current_path, n_files);
						refresh_interface(dirs);
						cursor_position = 0;
						dirs[current_dir].n_files = n_files;
						dirs[current_dir].cursor_position = cursor_position;
					}
					else {
						strcpy(current_path, last_path);
						print_error(strerror(result));
					}
				}
				else {
					print_error("La ruta '/' no tiene un directorio padre");
				}
			}
			else if (dir_content[current_dir][cursor_position].fileType == TEXTFILE) {
				char file_path[256];
				strcpy(file_path, current_path);
				if (strcmp(current_path, "/") != 0) {
					strcat(file_path, "/");
				}
				strcat(file_path, dir_content[current_dir][cursor_position].file_name);
				char *args[] = {"/usr/bin/wama/wama", "-r", &file_path[0], ZERO};
				int pid, status;
				if ((pid = forkexec(args[0], (const char **) args)) >= 0) {
					waitpid(pid, &status, 0);
				}
				refresh_interface(dirs);
			}
			else if (dir_content[current_dir][cursor_position].fileType == EXECUTABLE) {
				char exec_path[256];
				strcpy(exec_path, current_path);
				if (strcmp(current_path, "/") != 0) {
					strcat(exec_path, "/");
				}
				strcat(exec_path, dir_content[current_dir][cursor_position].file_name);
				char *args[] = {&exec_path[0], ZERO};
				int pid, status;
				if ((pid = forkexec(args[0], (const char **) args)) >= 0) {
					waitpid(pid, &status, 0);
				}
				refresh_interface(dirs);
			}
		}
		else if (key == INFO_KEY) {
			file_info(dir_content[current_dir][cursor_position].file_name, current_path);
			getchar();
			refresh_interface(dirs);
		}
		else if (key == ABOUT_KEY) {
			about_commander();
			getchar();
			refresh_interface(dirs);
		}
		else if (key == CREATE_FILE_KEY) {
			char filename[48];
			inicialice_var(filename);
			refresh_interface(dirs);
			print_entry(dir_content, dirs, current_dir);
			get_string("Introduzca el nombre del archivo de texto:", filename, 48);
			refresh_interface(dirs);
			char file_path[strlen(current_path)+strlen(filename)+1];
			inicialice_var(file_path);
			makePath(current_path, filename, file_path);
			char parent_path[strlen(file_path)];
			inicialice_var(parent_path);
			strcpy(parent_path, file_path);
			search_parent(parent_path);
			int result;
			if ((result = checkDir(parent_path)) == 0) {
				if (touch(file_path, S_IRUSR | S_IWUSR) < 0) {
					print_error(strerror(errno));
				}
				n_files = countFiles(current_path);
				free(dir_content);
				dir_content[current_dir] = get_dir_content(current_path, n_files);
			}
			else {
				print_error(strerror(result));
			}
		}
		else if (key == CREATE_DIR_KEY) {
			char dirname[48];
			inicialice_var(dirname);
			refresh_interface(dirs);
			print_entry(dir_content, dirs, current_dir);
			get_string("Introduzca el nombre del directorio:", dirname, 48);
			refresh_interface(dirs);
			char dir_path[strlen(current_path)+strlen(dirname)+1];
			inicialice_var(dir_path);
			makePath(current_path, dirname, dir_path);
			char parent_path[strlen(dir_path)];
			inicialice_var(parent_path);
			strcpy(parent_path, dir_path);
			search_parent(parent_path);
			int result;
			if ((result = checkDir(parent_path)) == 0) {
				if (mkdir(dir_path, S_IRUSR | S_IWUSR) < 0) {
					print_error(strerror(errno));
				}
				n_files = countFiles(current_path);
				free(dir_content);
				dir_content[current_dir] = get_dir_content(current_path, n_files);
			}
			else {
				print_error(strerror(result));
			}
		}
		else if (key == MOVE_KEY) {
			char new_path[256];
			refresh_interface(dirs);
			print_entry(dir_content, dirs, current_dir);
			get_string("Introduzca el nombre del directorio:", new_path, 256);
			int result;
			if ((result = checkDir(new_path)) == 0) {
				strcpy(current_path, new_path);
				refresh_interface(dirs);
				free(dir_content);
				n_files = countFiles(current_path);
				dir_content[current_dir] = get_dir_content(current_path, n_files);
				cursor_position = 0;
			}
			else {
				refresh_interface(dirs);
				print_error(strerror(result));
			}
		}
		else if (key == COPY_KEY) {
			char copy_file_path[256];
			strcpy(copy_file_path, current_path);
			if (strcmp(current_path, "/") != 0) strcat(copy_file_path, "/");
			strcat(copy_file_path, dir_content[current_dir][cursor_position].file_name);
			paste_filename = &dir_content[current_dir][cursor_position].file_name[0];
			int result;
			if ((result = checkDir(copy_file_path)) == ENOTDIR) {
				strcpy(copy_path, copy_file_path);
			}
			else if (!result) {
				print_error("Es un directorio");
			}
			else {
				print_error(strerror(result));
			}
		}
		else if (key == PASTE_KEY) {
			paste_file(copy_path, current_path, paste_filename);
			free(dir_content);
			n_files = countFiles(current_path);
			dir_content[current_dir] = get_dir_content(current_path, n_files);
		}
		else if (key != EXIT_KEY && key != UP_KEY && key != DOWN_KEY) {
			print_error("Comando Incorrecto");
		}
	}
	clean_screen();
}

int checkDir(char *path)
{
	int ret = 0;
	struct stat st;
	DIR *dir1;
	if (stat(path, &st) < 0) {
		ret = errno;
	}
	else if (S_ISDIR(st.st_mode)) {
		(!(dir1 = opendir(path))) ? ret = errno : closedir(dir1);
	}
	else {
		ret = ENOTDIR;
	}
	return ret;
}

void file_info(char *filename, char *path)
{
	char file_path[256];
	strcpy(file_path, path);
	if (strcmp(path, "/") != 0) {
		strcat(file_path, "/");
	}
	strcat(file_path, filename);
	struct stat st;
	if (stat(file_path, &st) < 0) {
		print_error(strerror(errno));
	}
	else {
		print_info(st, filename);
	}
}

void paste_file(char *copy_path, char *current_path, char *paste_filename)
{
		int result;
		char final_path[256];
		if ((result = checkDir(current_path)) == 0) {
			strcpy(final_path, current_path);
			if (strcmp(current_path, "/") != 0) strcat(final_path, "/");
			strcat(final_path, paste_filename);
			if (touch(final_path, S_IRUSR | S_IWUSR) < 0) {
				print_error(strerror(errno));
			}
			else if ((result = copy_file(copy_path, final_path)) != 0) {
				print_error(strerror(result));
			}
		}
		else {
			print_error(strerror(result));
		}
}
