/*
 * Copyright (C) 2014 Dan Rulos.
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

#include <stdio.h>
#include <VGA.h>

void error2(char *linea1, char *linea2, char *linea3)
{
    char tecla;
    int i;
    int idosr=0;
    u16 *vga;
    MemoryMessage mem;

    /* Request VGA memory. */
    mem.action    = CreatePrivate;
    mem.bytes     = PAGESIZE;
    mem.virtualAddress  = ZERO;
    mem.physicalAddress = VGA_PADDR;
    mem.protection      = PAGE_RW | PAGE_PINNED;
    mem.ipc(MEMSRV_PID, SendReceive, sizeof(mem));

    /* Point to the VGA mapping. */
    vga = (u16 *) mem.virtualAddress;
    for (i=0; i < 820; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    for (i=820; i < 860; i++) {
      vga[i] = VGA_CHAR(' ', RED, RED);
    }
    for (i=860; i < 900; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    for (i=900; i < 940; i++) {
      vga[i] = VGA_CHAR(' ', BLACK, RED);
    }
    for (i=902; idosr < strlen(linea1); i++) {
      vga[i] = VGA_CHAR(linea1[idosr], BLACK, RED);
      idosr++;
    }
    for (i=940; i < 980; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    for (i=980; i < 1020; i++) {
      vga[i] = VGA_CHAR(' ', BLACK, RED);
    }
    idosr=0;
    for (i=982; idosr < strlen(linea2); i++) {
      vga[i] = VGA_CHAR(linea2[idosr], BLACK, RED);
      idosr++;
    }
    for (i=1020; i < 1060; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    for (i=1060; i < 1100; i++) {
      vga[i] = VGA_CHAR(' ', BLACK, RED);
    }
    idosr=0;
    for (i=1062; idosr < strlen(linea3); i++) {
      vga[i] = VGA_CHAR(linea3[idosr], BLACK, RED);
      idosr++;
    }
    for (i=1100; i < 2000; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    bar(" [A] Aceptar [B] Instrucciones");
    do {
      tecla = getchar();
    } while (tecla != 'A'&& tecla != 'a'&& tecla != 'B'&& tecla != 'b');
    if (tecla == 'B'|| tecla == 'b') {
      error("Direccion - Flechas del teclado", " ", " ");
    }
}
