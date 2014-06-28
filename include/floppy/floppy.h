/*
    This file is part of Luxur & AmayaOS
    Copyright (C) 2010 - 2013 Esteban Misael Maltauro

    Luxur & Amaya OS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Luxur & Amaya OS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*Escrito por Andrea Righi*/


#define HZ 100



// Drive geometry for 1.44MB floppies //
#define FDC_SECTORS	18
#define FDC_HEADS	2
#define FDC_TRACKS	80
#define FDC_SECTOR_SIZE	512

// FDC motor spin up (msec) //
#define FDC_TIME_MOTOR_SPINUP	500

// FDC timeout to turn the motor off (msec) //
#define FDC_TIME_MOTOR_OFF	3000

// I/O ports //
#define FDC_DOR		0x3F2 // Digital Output Register
#define FDC_MSR		0x3F4 // Main Status Register (read)
#define FDC_DSR		0x3F4 // Data Rate Select Register (write)
#define FDC_DATA	0x3F5 // Data Register
#define FDC_DIR		0x3F7 // Digital Input Register
#define FDC_CCR		0x3F7 // Configuration Control Register

// Commands //
#define CMD_SPECIFY	0x03
#define CMD_WRITE	0xC5
#define CMD_READ	0xE6
#define CMD_RECAL	0x07
#define CMD_SENSEI	0x08
#define CMD_FORMAT	0x4D
#define CMD_SEEK	0x0F
#define CMD_VERSION	0x10

// Register flags //
#define MSR_BUSY	0x10

#define PAGE_SIZE	4096
#define PHYS_MEM_START		0xC0000000
#define PHYS_MEM_END		0xF0000000
#define PHYSICAL(addr)		(addr+PHYS_MEM_START)

// Floppy geometry structures //
typedef struct floppy_struct
{
	unsigned int 	size, 	// # of sectors total
		spt,	// sectors per track
		heads,	// # of heads
		tracks;	// # of tracks
	unsigned char	fmtgap,	// gap3 while formatting
		rwgap,	// gap3 while reading/writing
		rate;	// data rate
	char	*name;	// format name
} floppy_struct;

// Prototypes //
void floppy_handler();
void floppy_thread();
void init_floppy();

void fdc_motor_on();
void fdc_motor_off();

void fdc_recalibrate();
int fdc_seek(int track);
int fdc_read(int block, unsigned char *buffer, unsigned int count);
int fdc_write(int block, unsigned char *buffer, unsigned int count);



