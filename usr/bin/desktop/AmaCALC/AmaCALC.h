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

#define AMACALC_V "0.4"

/* get_s() fork */
char *get_input_csv(char *str, size_t size);

/* returns 0 if a char is a number 
 * and 1 if not
 */
int numberyn(char number);

/* returns a letter code 
 * 0 A
 * 1 B
 * 2 C
 * 3 D
 * 4 E
 * 5 F
 */
int get_letter(char *c, int rp);

/* returns the number of lines in 'c' */
int get_point(char *c, int izq);

/* write 'c' in file 'fd' using the mode 'mode'
 * 'c' is the line to write
 * 'fd' is the file descriptor
 * 'mode' is the write mode
 */
void writter_csv(char *c, int fd, int mode);

/* cleans the internal command and print 'res' */
void print_line(char *line, char *res);

/* returns 0 if letter == 'A'...*/
int get_letter_num(char letter);

/* check if line it's a valid amacalc command 
 * returns 0 if yes
 * returns a negative number if not
 */
int checkCommand(char *line);
