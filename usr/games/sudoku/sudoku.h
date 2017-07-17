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


#define LOST 0
#define WIN 1

/* clear_window() cleans the screen */
void clear_window();

/* put sudoku on the screen */
void print_sudoku(unsigned int *numbers, int act_pos);

/* Creates a Sudoku valid array from a file */
unsigned int getSudokuFromFile(char *path, unsigned int *Sudoku);
