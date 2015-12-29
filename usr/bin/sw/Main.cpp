/*
 * Copyright (C) 2015 Dan Rulos
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

#define VERSION "0.03"

int main(int argc, char **argv)
{
	int result = EXIT_SUCCESS;
	if (argc != 1) {
		if ((strcmp(argv[1], "--version")) == 0) {
			printf("sw (Sea War) v%s\n", VERSION);
		}
		else if ((strcmp(argv[1], "--help")) == 0) {
			printf("sw (Sea War) v%s\n", VERSION);
			printf("Copyright (C) 2015 AmayaOS Team\n");
			printf("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n");
			printf("This is free software: you are free to change and redistribute it.\n");
			printf("There is NO WARRANTY, to the extent permitted by law.\n");
		}
		else {
			printf("%s: argumento invalido '%s'\n", argv[0], argv[1]);
		}
	}
	else {
		result = sw();
	}
	return result;
}
