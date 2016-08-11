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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* sea war game */
#include "sw.h"

#define VERSION "0.3"

void help(void);

int main(int argc, char **argv)
{
	int result = EXIT_SUCCESS;
	int mode = 0;
	int flag = 0;
	if (argc >= 2) {
		for (int i = 1; i < argc && !flag && result != EXIT_FAILURE; i++) {
			if ((strcmp(argv[i], "--version")) == 0) {
				printf("sw (Sea War) v%s\n", VERSION);
				flag = 1;
			}
			else if ((strcmp(argv[i], "--help")) == 0) {
				help();
				flag = 1;
			}
			else if ((strcmp(argv[i], "--mode") == 0) && (i+1) < argc) {
				if (strcmp(argv[++i], "single") == 0) mode = 0;
				else if (strcmp(argv[i], "multi") == 0) mode = 1;
				else {
					printf("'%s' no es un modo juego v%clido\n", argv[i], 160);
					result = EXIT_FAILURE;
				}
			}
			else {
				printf("%s: argumento invalido '%s'\n", argv[0], argv[i]);
				result = EXIT_FAILURE;
			}
		}
	}
	if (!flag && result != EXIT_FAILURE) result = sw(mode);
	return result;
}

void help(void)
{
	printf("sw (Sea War) v%s\n", VERSION);
	printf("Copyright (C) 2015, 2016 AmayaOS Team\n");
	printf("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n");
	printf("This is free software: you are free to change and redistribute it.\n");
	printf("There is NO WARRANTY, to the extent permitted by law.\n");
	printf("--help\t\t\tPrints this help and exit\n");
	printf("--version\t\tPrints Sea War version and exit\n");
	printf("--mode [GAMEMODE]\tSet a new default gamemode\n");
}
