/*
 * Copyright (C) 2015 Dan Rulos
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
#include <amaya.h>

void clean()
{
    char clean_char[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
    printf("%s", clean_char);
}

void game()
{
    int i;
    char tecla;
    int ia[5] = { 38, 39, 40, 41, 42 };
    int player[5] = { 1958, 1959, 1960, 1961, 1962 };
    int valor=0;
    int ball=1000;
    int point=0;
    int speed=81;
    error("Pong v0.1", "Player 1: Flechas del teclado", "Player 2: Teclas Z y X");
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

    do {
        for (i=0; i < 2000; i++) {
	   vga[i] = VGA_CHAR(' ', BLACK, BLACK);
        }
	vga[ball] = VGA_CHAR(' ', BLUE, BLUE);
	for (i=0; i <= 4; i++) {
	  vga[ia[i]] = VGA_CHAR(' ', WHITE, WHITE);
	}
	for (i=0; i <= 4; i++) {
	  vga[player[i]] = VGA_CHAR(' ', WHITE, WHITE);
	}
	tecla = getchar();
	if (tecla == 'd' && player[4] < 1999) {
	  for (i=0; i <= 4; i++) {
	     player[i]++;
	  }
	}
	if (tecla == 'b' && player[0] > 1920) {
	  for (i=0; i <= 4; i++) {
	     player[i]--;
	  }
	}
	if (tecla == 'x' && ia[4] < 80) {
	  for (i=0; i <= 4; i++) {
	     ia[i]++;
	  }
	}
	if (tecla == 'z' && ia[0] > 0) {
	  for (i=0; i <= 4; i++) {
	     ia[i]--;
	  }
	}
	if (ball < 80) {
	  valor++;
	}
	if (ball > 1919) {
	  valor--;
	}
	if (ball == ia[0]+80 || ball == ia[1]+80 || ball == ia[2]+80) {
	  speed=81;
	}
	if (ball == ia[3]+80 || ball == ia[4]+80) {
	  speed=79;
	}
	if (ball == player[0]-80 || ball == player[1]-80 || ball == player[2]-80) {
	  speed=-79;
	  point++;
	}
	if (ball == player[3]-80 || ball == player[4]-80) {
	  speed=-81;
	  point++;
	}
	/* We calculate the ball position in the screen */
	ball=ball+speed;
    } while(valor == 0);
    /* Cleaning screen */
    clean();
    printf("Juego terminado\r\n");
    if (valor == 1) {
	printf("Has ganado\r\nPuntuacion total: %d puntos\r\n", point);
    }
    if (valor == -1) {
	printf("Has perdido\r\nPuntuacion total: %d puntos\r\n", point);
    }
    printf("Pulsa una tecla\r\n");
    getchar();
    int argc;
    char **argv;
    main(argc, argv);
}
