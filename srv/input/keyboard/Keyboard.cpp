/*
 * Copyright (C) 2009 Niek Linnenbank, 2014 Dan Rulos.
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

#include <API/ProcessCtl.h>
#include <Macros.h>
#include <Error.h>
#include <Config.h>
#include "Keyboard.h"

/**
 * Temporary hardcoded keyboard map, from kb.c in SkelixOS.
 * @see http://www.skelix.org
 */
/**
 * 0x3A - Caps/Mayus
 * 0x3B - F1
 * 0x3C - F2
 * 0x3D - F3
 * 0x3E - F4
 * 0x3F - F5
 * 0x40 - F6
 * 0x41 - F7
 * 0x42 - F8
 * 0x43 - F9
 * 0x44 - F10
 * 0x57 - F11
 * 0x58 - F12
 * 0x48 - Up/Arriba
 * 0x4B - Left/Izquierda
 * 0x4D - Right/Derecha
 * 0x50 - Down/Abajo
 * 0x52 - INS
 * 0x53 - Del/Supr
 */

const char Keyboard::keymap[0x3a][2] =
{
    /*00*/{0x0, 0x0}, {0x0, 0x0}, {'1', '!'}, {'2', '@'}, 
    /*04*/{'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '&'}, 
    /*08*/{'7', '/'}, {'8', '('}, {'9', ')'}, {'0', '='},
    /*0c*/{'*', '?'}, {'/', 168}, {'\b','\b'},{'\t','\t'},
    /*10*/{'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'},
    /*14*/{'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'},
    /*18*/{'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'},
    /*1c*/{'\n','\n'},{0x0, 0x0}, {'a', 'A'}, {'s', 'S'},
    /*20*/{'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'},
    /*24*/{'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {164, 165},
    /*28*/{'\'','\"'},{'`', '~'}, {0x0, 0x0}, {'Ç','Ç'}, 
    /*2c*/{'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, 
    /*30*/{'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', ';'},
    /*34*/{'.', ':'}, {'-', '_'}, {0x0, 0x0}, {'/', '*'},
    /*38*/{0x0, 0x0}, {' ', ' '}
};

Keyboard::Keyboard() : shiftState(ZERO)
{
}

Error Keyboard::initialize()
{
    return ProcessCtl(SELF, AllowIO,  PS2_PORT);
}

Error Keyboard::interrupt(Size vector)
{
    pending = true;
    return ESUCCESS;
}

Error Keyboard::read(s8 *buffer, Size size, Size offset)
{
    /* Do we have any new key events? */
    if (pending)
    {
	pending = false;
    
	/*
         * Read byte from the keyboard.
         */
        u8 keycode = inb(PS2_PORT);

        /* Update shift state. */
        if (keycode == 0x2a || keycode == 0xaa)
        {
    	    shiftState ^= 1;
	}
        /* Don't do anything on release. */
	else if (!(keycode & PS2_RELEASE) &&
	          (keymap[keycode & 0x7f][shiftState]))
	{
	    /* Write to buffer. */
	    buffer[0] = keymap[keycode & 0x7f][shiftState];
    	    return 1;
	}
    }
    return EAGAIN;
}
