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

#ifndef SEA_WAR_H_INCLUDED 
#define SEA_WAR_H_INCLUDED

/**
 * clear_window() cleans the screen *
 */

extern C void clear_window();

/**
 * print_map() puts the map "game_map" on Window *
 */

extern C void print_map();


/**
 * put_ship_on_map() puts the ships position on the game map *
 */

extern C void put_ship_on_map(int mode);

/**
 * sw() is the main function of the game Sea War *
 * @return EXIT_SUCCESS or EXIT_FAILURE (stdlib.h) */

extern C int sw();

#endif
