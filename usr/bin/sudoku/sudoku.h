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


#define LOST 0
#define WIN 1

/* clear_window() cleans the screen */
void clear_window();

/* put sudoku on the screen */
void print_sudoku(int *numbers, int act_pos);

/* returns a random number from 0 to 9 */
int randomnumber();

/* make_sudoku() returns the value of a position (pos) in a sudoku
 */
int make_sudoku(int pos, char *path);
