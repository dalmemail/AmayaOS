/*
 * Copyright (C) 2017 Daniel Martín
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

#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "Shell.h"

unsigned int countFiles(char *path)
{
	unsigned int file_count = 0;
	DIR *d;
	struct dirent *dent;
	if ((d = opendir(path))) {
		while ((dent = readdir(d))) {
			file_count++;
		}
	}
	return file_count;
}

unsigned int cmpEntry(char *a, char *b)
{
	unsigned int cmpRet = 1;
	unsigned int size_a = strlen(a);
	unsigned int size_b = strlen(b);
	unsigned int i;
	if (size_a >= size_b) {
		for (i = 0; i < size_b; i++) {
			if (a[i] != b[i]) cmpRet = 0;
		}
	}
	else cmpRet = 0;
	return cmpRet;
}

unsigned int tab_completion(char *line, unsigned int line_max, unsigned int total)
{
	int i;
	for (i = total; line[i] != ' ' && i >= 0; i--);
	char *wkline = &line[i+1];
	DIR *d;
	struct dirent *dent;
	char path[128] = "\0";
	char uncompleted[64] = "\0";
	if (total == 0 || wkline[0] != '/') {
		getcwd(path, sizeof(path));
		strlcpy(uncompleted, wkline, sizeof(uncompleted));
	}
	else {
		for (i = total; wkline[i] != '/' && i > 0; i--);
		wkline[i] = '\0';
		if (i == 0) strlcpy(path, "/\0", sizeof(path));
		else strlcpy(path, wkline, sizeof(path));
		strlcpy(uncompleted, &wkline[i+1], sizeof(uncompleted));
	}
	if (!(d = opendir(path))) {
		return strlen(line);
	}
	unsigned int d_entries = countFiles(path);
	char PossibleFiles[d_entries][64];
	unsigned int n_pf = 0;
	while ((dent = readdir(d))) {
		if (cmpEntry(dent->d_name, uncompleted)) {
			strlcpy(PossibleFiles[n_pf++], dent->d_name, sizeof(PossibleFiles[n_pf-1]));
			//if (dent->d_type == DT_DIR) strcat(PossibleFiles[n_pf-1], "/\0");
		}
	}
	closedir(d);
	if (n_pf == 1) {
		printf("%s", &PossibleFiles[0][strlen(uncompleted)]);
		strlcpy(uncompleted, PossibleFiles[0], sizeof(uncompleted));
	}
	else if (n_pf > 1) {
		printf("\n");
		for (i = 0; i < n_pf; i++) printf("%s ", PossibleFiles[i]);
	}
	if (total == 0 || (wkline[0] != '/' && strcmp(path, "/"))) strcpy(wkline, uncompleted);
	else if (strcmp(path, "/")) snprintf(wkline, (line_max-strlen(line)), "%s/%s", path, uncompleted);
	else snprintf(wkline, (line_max-strlen(line)), "/%s", uncompleted);
	if (n_pf > 1) {
		printf("\n");
		prompt();
		printf("%s", line);
	}
	return strlen(line);
}
