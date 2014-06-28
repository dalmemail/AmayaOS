/*
    This file is part of Luxur
    Copyright (C) 2010 - 2013 Esteban Misael Maltauro

    Luxur is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Luxur is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//driver del floppy..lo consegui por internet. la verdad no se quien lo escribio.

#include <timer.h>
#include <dma.h>
#include <es.h>
#include <stdio.h>
#include <floppy/floppy.h>
#include <isr.h>


volatile int fdc_motor = 0;


volatile int fdc_timeout = 0;


volatile int fdc_motor_countdown=0;


volatile int fdc_done = 0;


volatile int fdc_change = 0;


volatile unsigned char fdc_status[7] = { 0 };


volatile unsigned char fdc_track = 0xFF;


volatile unsigned char ST0 = 0;


static floppy_struct floppy_type[] = {
{ 2880, 18, 2, 80, 0x54, 0x1B, 0x00, "H1440" },	// 1.44MB
{ 3360, 21, 2, 80, 0x0C, 0x1C, 0x00, "H1680" }	// 1.68MB
};


unsigned char fdc_geometry = 0;


unsigned char *fdc_buffer;




void fdc_sendbyte(unsigned char b)
{

	int msr;
	int tmo;

	for (tmo=0; tmo<128; tmo++)
	{
		msr = inb(FDC_MSR);
		if ((msr & 0xC0) == 0x80)
		{
			outportb(FDC_DATA, b);
			return;
		}
		inb(0x80); 
	}
}

int fdc_getbyte() 
{

	int msr;
	int tmo;

	for (tmo=0; tmo<128; tmo++)
	{
		msr = inb(FDC_MSR);
		if ((msr & 0xD0) == 0xD0)
			return(inb(FDC_DATA));
		inb(0x80); 
	}
	return(-1); 
}

void fdc_motor_on() 
{

	if (!fdc_motor)
	{
		outportb(FDC_DOR, 0x1C);
		timer_wait(FDC_TIME_MOTOR_SPINUP);
		fdc_motor = 1;
	}
	fdc_motor_countdown = -1;
}

void fdc_motor_off()
{

	if (fdc_motor && (fdc_motor_countdown==-1))
		fdc_motor_countdown = FDC_TIME_MOTOR_OFF/1000*HZ;
}

int fdc_wait(int sensei) 
{
	unsigned char i;

	fdc_timeout = HZ; 

	
	while((!fdc_done) && (fdc_timeout))
	{
                sti();
		
		idle();
               
               
	}

	
	i = 0;
	while ((i < 7) && (inb(FDC_MSR) & MSR_BUSY))
		fdc_status[i++] = fdc_getbyte();

	
	if (sensei)
	{
		fdc_sendbyte(CMD_SENSEI);
		ST0 = fdc_getbyte();
		fdc_track = fdc_getbyte();
	}

	// Timed out? //
	if (!fdc_done)
	{
		
		if (inb(FDC_DIR) & 0x80)
			fdc_change = 1;
		return(0);
	}
	else
	{
		fdc_done = 0;
		return(1);
	}
}

void fdc_recalibrate()
{


	
	fdc_motor_on();

	
	fdc_sendbyte(CMD_RECAL);
	fdc_sendbyte(0);

	
	fdc_wait(1);

	
	fdc_motor_off();
}

int fdc_seek(int track) 
{


	
	if (fdc_track == track)
		return(1);

	
	fdc_motor_on();

	
	fdc_sendbyte(CMD_SEEK);
	fdc_sendbyte(0);
	fdc_sendbyte(track);

	
	if (!fdc_wait(1))
	{
		// Timeout! //
		fdc_motor_off();
		return(0);
	}

	
	timer_wait(15);

	
	fdc_motor_off();

	
	if ((ST0 != 0x20) || (fdc_track != track))
		return(0);
	else
		return(1);
}

void fdc_reset() 
{
	
	outportb(FDC_DOR, 0x00);

	
	outportb(FDC_DSR, 0x00);

	
	outportb(FDC_DOR, 0x0C);

	
	fdc_done = 1;
	fdc_wait(1);

	
	fdc_sendbyte(CMD_SPECIFY);
	fdc_sendbyte(0xDF); 
	fdc_sendbyte(0x02); 

	
	fdc_seek(1);
	fdc_recalibrate();
	fdc_change = 0;
}

void lba2chs(int lba, int *track, int *head, int *sector) 
{
	*track = lba / (floppy_type[fdc_geometry].spt * floppy_type[fdc_geometry].heads);
	*head = (lba / floppy_type[fdc_geometry].spt) % floppy_type[fdc_geometry].heads;
	*sector = (lba % floppy_type[fdc_geometry].spt) + 1;
}

int fdc_rw(int block, unsigned char *buffer, int do_read)
{
	int track, head, sector, tries;

	
	lba2chs(block, &track, &head, &sector);

	
	fdc_motor_on();

	if (!do_read)
		
		memcpy(fdc_buffer, buffer, FDC_SECTOR_SIZE);

	for(tries=0; tries<3; tries++)
	{
		
		if (inb(FDC_DIR) & 0x80)
		{
			fdc_change = 1;
			fdc_seek(1);
			fdc_recalibrate();
			fdc_motor_off();
			return(0);
		}
		
		if (!fdc_seek(track))
		{
			fdc_motor_off();
			return(0);
		}
		
		outportb(FDC_CCR, floppy_type[fdc_geometry].rate);

		
		if (do_read)
		{
			
			dma_xfer(2, (unsigned int)fdc_buffer, FDC_SECTOR_SIZE, 0);
			fdc_sendbyte(CMD_READ);
		}
		else
		{
			
			dma_xfer(2, (unsigned int)fdc_buffer, FDC_SECTOR_SIZE, 1);
			fdc_sendbyte(CMD_WRITE);
		}
		fdc_sendbyte(head << 2);
		fdc_sendbyte(track);
		fdc_sendbyte(head);
		fdc_sendbyte(sector);
		fdc_sendbyte(2); 
		fdc_sendbyte(floppy_type[fdc_geometry].spt);
		fdc_sendbyte(floppy_type[fdc_geometry].rwgap);
		fdc_sendbyte(0xFF); 

		
		if (!fdc_wait(0))
			return(0); 

		if ((fdc_status[0] & 0xC0) == 0) break; 

		
		fdc_recalibrate();
	}

	
	fdc_motor_off();

	if (do_read)
		
		memcpy(buffer, fdc_buffer, FDC_SECTOR_SIZE);

	
	return(tries != 3);
}

int fdc_read(int block, unsigned char *buffer, unsigned int count)
{

	register int i;

	for(i=0; i<count; i++)
		if (!(fdc_rw(block, buffer+FDC_SECTOR_SIZE*i, 1)))
			return(0);
	
	return(1);
}

int fdc_write(int block, unsigned char *buffer, unsigned int count)
{

	register int i;

	for(i=0; i<count; i++)
		if (!(fdc_rw(block, buffer+FDC_SECTOR_SIZE*i, 0)))
			return(0);
	
	return(1);
}

void floppy_thread()
{

	if (fdc_timeout > 0)
		fdc_timeout--;

	if (fdc_motor_countdown > 0)
		fdc_motor_countdown--;
	else if (fdc_motor && !fdc_motor_countdown)
	{
		outportb(FDC_DOR, 0x0C);
		fdc_motor = 0;
	}
}

void floppy_handler()
{

	fdc_done = 1;
}

void init_floppy()
{

	int v;
        register_interrupt_handler(IRQ6, &floppy_handler);
	
        
	fdc_buffer = (unsigned char *)kmalloc(dma_pop_frame()*PAGE_SIZE);
        
	
	fdc_reset();
        
	
	fdc_sendbyte(CMD_VERSION);
        
	v = fdc_getbyte();
       
	/*if (v==0x90)
		printf("\nEnhanced controller found!");
	else
		printf("\n8272A/765A controller found!");
        */
}
