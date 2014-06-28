/*
 * Copyright (C) 2012 Felipe Cabrera
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

#include <Device.h>
#include <Types.h>
#include <Macros.h>
#include <Error.h>

class Stdin : public Device
{
    public:
    
        /** 
         * @brief Opens the null device.
     *
     * This function currently opens the system console
     * to perform all logging operations.
     *
         * @return Error result code. 
         */
    Error initialize();

        /** 
         * Read a null byte.
         * @param buffer Buffer containing bytes to read. 
         * @param size Nothing.
         * @return Always return 0. 
         */
    Error read(s8 *buffer, Size size, Size offset);
};