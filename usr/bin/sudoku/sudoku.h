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


#define LOST 0
#define WIN 1

#define EASY 0
#define DIFFICULT 1
#define COMPETITION_EASY 2
#define COMPETITION_DIFF 3
#define LOAD_SUDOKU 4

/* clear_window() cleans the screen */
void clear_window();

/* get a num from the keyboard and return it.
 * if key is \b returns -1
 */
int getnum();

/* put sudoku on the screen */
void print_sudoku(int *numbers);

/* returns a random number from 0 to 9 */
char randomnumber();

/* make_sudoku() returns the value of a position (pos) in a sudoku
 */
int make_sudoku(int pos, char *path);
