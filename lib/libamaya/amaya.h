/*
 * Copyright (C) 2014 Dan Rulos.
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

/* PAUSE is a extra function of AmayaOS used to stop the program with a
   Press any key message on stdin. */
extern C void pause();

/* window() make a new window on desktop */
/* titulo The name to be will print */
/* start (0-79) Where want you print the name ? */
extern C void window(char *titulo, int start);

/* bg() put the color on the window background */
extern C void bg();

/* bar() print the options on the down bar */
extern C void bar(char *options);

/* error() print error message */
extern C void error(char *linea1, char *linea2, char *linea3);
