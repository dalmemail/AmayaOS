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

#define isDelim(x) (x == ' ' || x == '\n')
#define isToken(x) (x != ' ' && x != '\n')

unsigned int sw = 0;
unsigned int tw = 0;
unsigned char w_readTokens = 1, w_readDelimiters = 1;

void wordCounter(char c)
{
	if(c == -1) return;

	if(isToken(c) && w_readTokens)
	{
		sw++;
		w_readTokens = 0;
		w_readDelimiters = 1;
	}

	if(isDelim(c) && w_readDelimiters)
	{
		w_readDelimiters = 0;
		w_readTokens = 1;
	}
}

void resetWordCounter()
{
	tw += sw;
	sw = 0;
	w_readTokens = 1;
	w_readDelimiters = 1;
}
