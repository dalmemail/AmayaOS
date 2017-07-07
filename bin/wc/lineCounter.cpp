/*
 * Copyright (C) 2016 SuperTau, 2017 Daniel Martín
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

unsigned int sl = 0;
unsigned int tl = 0;
char lineCounter_old = 0;

void lineCounter(char c)
{
	if((c == '\n') || (c == -1 && lineCounter_old != '\n')) sl++;
	lineCounter_old = c;
}

void resetLineCounter()
{
	tl += sl;
	sl = 0;
	lineCounter_old = 0;
}
