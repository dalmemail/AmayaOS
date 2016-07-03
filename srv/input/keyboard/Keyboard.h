/*
 * Copyright (C) 2009 Niek Linnenbank, 2016 Dan Rulos.
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

#ifndef __INPUT_KEYBOARD_H
#define __INPUT_KEYBOARD_H

/**
 * @defgroup ps2 PS2 Keyboard (IBM Personal System/2 Keyboard)  
 * @{  
 */

#include <Device.h>
#include <Macros.h>
#include <Types.h>
#include <Error.h>

/** PS2 Keyboard input port. */
#define PS2_PORT        0x60

/** Interrupt number of the i8042 controller. */
#define PS2_IRQ         1

/** Bit is set in the scancode, if a key is released. */
#define PS2_RELEASE     0x80 

/* Supported Modified Keys */
#define NO_MODIFIER_KEY 0
#define SHIFT_KEY 1
#define ALT_GR_KEY 2

/**
 * @brief PS2 Keyboard device driver.
 */
class Keyboard : public Device
{
    public:

        /**
         * @brief Constructor function.
         */
	Keyboard();

	/**
	 * @brief Initialize the PS2 Keyboard driver.
	 * @return Error status code.
	 */
	Error initialize();

	/**
	 * @brief Executed when a key state has changed.
	 * @param vector Interrupt vector.
	 * @return Error status code.
	 */
	Error interrupt(Size vector);

	/**
	 * @brief Read a character from the keyboard.
	 *
	 * @param buffer Output buffer.
	 * @param size Number of bytes to read.
	 * @param offset Unused.
	 * @return Number of bytes read or error code on failure.
	 */
	Error read(s8 *buffer, Size size, Size offset);

    private:

	/**
	 * @brief Keyboard map table.
	 */
        static const char keymap[0x80][3];

	/**
	 * @brief State of the modifiers keys.
	 *
	 * 0 : No modifier key is pressed.
	 * 1 : Shift Key is pressed.
	 * 2 : AltGr Key is pressed.
	 */
	int modifierKey;
	
	/** Do we have a byte ready? */
	bool pending;
};

/**
 * @}
 */

#endif /* __INPUT_KEYBOARD_H */
