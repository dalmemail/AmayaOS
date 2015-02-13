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
#include <unistd.h>

void game()
{
    int i;
    char tecla;
    int ia[10] = { 36, 37, 38, 39, 40, 41, 42, 43, 44, 45 };
    int player[10] = { 1956, 1957, 1958, 1959, 1960, 1961, 1962, 1963, 1964, 1965 };
    int valor=0;
    int ball=1000;
    int point=0;
    int speed=81;
    error("Pong v0.1", "Player 1: Teclas A y D", "Pulsa A para jugar");
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
	for (i=0; i <= 9; i++) {
	  vga[ia[i]] = VGA_CHAR(' ', WHITE, WHITE);
	}
	for (i=0; i <= 9; i++) {
	  vga[player[i]] = VGA_CHAR(' ', WHITE, WHITE);
	}
	if (speed > 0) {
	  tecla = getchar();
	}
	else {
	  sleep(1);
	}
	/* Ball position */
	if (ball == 79 || ball == 159 || ball == 239 || ball == 319 || ball == 399 || ball == 479 || ball == 559 || ball == 639 || ball == 719 || ball == 799 || ball == 879 || ball == 959 || ball == 1039 || ball == 1119 || ball == 1199 || ball == 1279 || ball == 1359 || ball == 1439 || ball == 1519 || ball == 1599 || ball == 1679 || ball == 1759 || ball == 1839 || ball == 1919 || ball == 1999) {
	  if (speed == 81) {
	    speed = 79;
	  }
	  if (speed == -79) {
	    speed = -81;
	  }
	}
	if (ball == 80 || ball == 160 || ball == 240 || ball == 320 || ball == 400 || ball == 480 || ball == 560 || ball == 640 || ball == 720 || ball == 800 || ball == 880 || ball == 960 || ball == 1040 || ball == 1120 || ball == 1200 || ball == 1280 || ball == 1360 || ball == 1440 || ball == 1520 || ball == 1600 || ball == 1680 || ball == 1760 || ball == 1840 || ball == 1920) {
	  if (speed == 79) {
	    speed = 81;
	  }
	  if (speed == -81) {
	    speed = -79;
	  }
	}
	if (tecla == 'd' && player[9] < 1999) {
	  for (i=0; i <= 9; i++) {
	     player[i]++;
	  }
	}
	if (tecla == 'a' && player[0] > 1920) {
	  for (i=0; i <= 9; i++) {
	     player[i]--;
	  }
	}
	/* Starting ia (bot) */
	if (speed == -79 && ia[9] < 79) {
	  for (i=0; i <= 9; i++) {
		ia[i]++;
		ia[i]++;
	  }
	}
	if (speed == -81 && ia[0] >= 0) {
	  for (i=0; i <= 9; i++) {
		ia[i]--;
		ia[i]--;
	  }
	}
	if (speed > 0) {
	  if (ia[4] < 39) {
	    for (i=0; i <= 9; i++) {
		ia[i]++;
	    }
	  }
	  if (ia[4] > 39) {
	    for (i=0; i <= 9; i++) {
		ia[i]--;
	    }
	  }
	}
	if (ball < 80) {
	  /* If 'valor' is 1 you win */
	  valor++;
	}
	if (ball > 1919) {
	  /* If 'valor' is -1 you lost */
	  valor--;
	}
	/* Warning with IA position */
	if (ia[9] >= 80) {
	  for (i=0; i <= 9; i++) {
	     ia[i]--;
	  }
	}
	if (ia[9] <= 0) {
	  for (i=0; i <= 9; i++) {
	     ia[i]++;
	  }
	}
	if (ball == ia[0]+80 || ball == ia[1]+80 || ball == ia[2]+80 || ball == ia[3]+80 || ball == ia[4]+80 || ball == ia[5]+80 || ball == ia[6]+80 || ball == ia[7]+80 || ball == ia[8]+80 || ball == ia[9]+80) {
	  if (speed == -81) {
	    speed = 79;
	  }
	  if (speed == -79) {
	    speed = 81;
	  }
	}
	if (ball == player[0]-80 || ball == player[1]-80 || ball == player[2]-80 || ball == player[3]-80 || ball == player[4]-80 || ball == player[5]-80 || ball == player[6]-80 || ball == player[7]-80 || ball == player[8]-80 || ball == player[9]-80) {
	  if (speed == 79) {
	    speed = -81;
	  }
	  if (speed == 81) {
	    speed = -79;
	  }
	  point++;
	}
	/* We calculate the ball position in the screen */
	ball=ball+speed;
	/* We reset 'tecla' */
	tecla=' ';
    } while(valor == 0);
    /* Cleaning screen */
    char clean[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
    printf("%s", clean);
    printf("Juego terminado\r\n");
    if (valor == 1) {
	printf("Has ganado\r\nPuntuacion total: %d puntos\r\n", point);
    }
    if (valor == -1) {
	printf("Has perdido\r\nPuntuacion total: %d puntos\r\n", point);
    }
    printf("Pulsa una tecla\r\n");
    getchar();
}
