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

#define N_SUDOKUS 20

unsigned int sudb[][16] = {
	{ 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 3, 0, 2, 0, 0 },
	{ 4, 0, 0, 3, 0, 2, 0, 0, 2, 0, 4, 0, 0, 0, 0, 0 },
	{ 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 4, 0, 0, 0 },
	{ 0, 4, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 3 },
	{ 2, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 4, 1, 0 },
	{ 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0 },
	{ 0, 0, 2, 0, 0, 3, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 2, 0, 0, 4, 0, 3, 0, 0, 0, 0 },
	{ 0, 2, 0, 0, 0, 0, 0, 4, 2, 0, 0, 0, 0, 0, 0, 3 },
	{ 2, 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0 },
	{ 2, 1, 0, 0, 0, 3, 2, 0, 0, 0, 0, 4, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 4, 0, 0, 2, 2, 0, 0, 4, 0, 0, 2, 3 },
	{ 4, 0, 0, 0, 0, 0, 1, 0, 0, 2, 4, 0, 0, 0, 2, 1 },
	{ 0, 2, 1, 0, 0, 0, 3, 2, 0, 1, 0, 0, 2, 0, 0, 1 },
	{ 0, 0, 0, 3, 0, 4, 0, 2, 0, 0, 2, 1, 1, 0, 0, 0 },
	{ 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 4, 1, 2, 0 },
	{ 0, 2, 0, 0, 1, 0, 0, 2, 3, 0, 0, 4, 0, 0, 1, 0 },
	{ 2, 4, 0, 0, 0, 0, 2, 0, 4, 0, 0, 1, 0, 3, 0, 0 },
	{ 0, 3, 0, 0, 0, 1, 0, 0, 3, 0, 1, 0, 1, 0, 2, 0 },
	{ 1, 0, 0, 0, 3, 0, 1, 0, 0, 0, 0, 4, 0, 3, 2, 0 }
};
