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

#include <amaya.h>

int aleatorio()
{
    /* Nos aprovechamos del contador 'time' para hacer un número medianamente aleatorio */
    file *f = new file();
    f->setpath("/dev/time");
    f->f_open(O_RDONLY);
    char *ch = f->readAll();
    f->f_close();
    if (ch[8] == '0') {
    	switch (ch[9]) {
		case '0':
			return 0;
			break;
		case '1':
			return 1;
			break;
		case '2':
			return 2;
			break;
		case '3':
			return 3;
			break;
		case '4':
			return 4;
			break;
		case '5':
			return 5;
			break;
		case '6':
			return 6;
			break;
		case '7':
			return 7;
			break;
			case '8':
			return 8;
			break;
		case '9':
			return 9;
		break;
    	}	
    }
    else {
	char num[2] = {ch[8], ch[9]};
	return atoi(num);
    }
}

int hangman()
{
	/* numero de intentos (max 10)*/
	int intentos=0;
	char key='\b';
	char words[30][128] = {"ornitorrinco", "gato", "buho", "manzana", "aerogenerador", "arbol", "policia", "noviembre",
			     "carta", "entrada", "flor", "inteligencia", "chocolate", "literatura", "galleta", "movil",
			     "ordenador", "chimenea", "caramelo", "cucaracha", "mesa", "ardilla", "ventana", "llaves",
			     "ladrillo", "coche", "bombilla", "vino", "bicicleta", "atracciones"};
	char word[128];
	char fails[128];
	for (int w=0; w < 128; w++) {
		fails[w] = ' ';
	}
	int z=0;
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	int n = aleatorio();
	if (n > 29) {
		n = n / 2;
		if (n > 29) {
			n = n / 2;
		}
	}
	printf("%s", str);
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
	for (int i=0; i <= 127; i++) {
		word[i] = '_';
	}
	/* bucle principal del juego */
	while(1) {
		/* ponemos el color de fondo */
		for (int i=0; i <= 2000; i++) {
			vga[i] = VGA_CHAR(' ', BROWN, BROWN);
		}
		/*titulo de la ventana */
		window("AmayaOS Hangman", 2);
		/* cuadro de texto */
		for (int i=321; i >= 0; i++) {
			vga[i] = VGA_CHAR(' ', GREEN, GREEN);
			switch (i) {
				case 350:
					i = 400;
					break;
				case 430:
					i = 480;
					break;
				case 510:
					i = 560;
					break;
				case 590:
					i = -2;
					break;
			}
			for (int i=0; i < strlen(words[n]); i++) {
				vga[409+i] = VGA_CHAR(word[i], BLACK, GREEN);
			}
		}
		for (int i=361; i >= 0; i++) {
			vga[i] = VGA_CHAR(' ', GREEN, GREEN);
			if (i == 390 || i == 470 || i == 550 || i == 630 || i == 710 || i == 790 ||
			    i == 870 || i == 950 || i == 1030 || i == 1110 || i == 1190 || i == 1270 ||
			    i == 1350 || i == 1430 || i == 1510 || i == 1590 || i == 1670 || i == 1750 || i == 1830) {
				i = i+50;
			}
			if (i >= 1880) {
				i = -2;
			}
		}
		if (intentos >= 0) {
			vga[1572] = VGA_CHAR('-', BLACK, GREEN);
			vga[1573] = VGA_CHAR('-', BLACK, GREEN);
			vga[1574] = VGA_CHAR('-', BLACK, GREEN);
			vga[1575] = VGA_CHAR('-', BLACK, GREEN);
			vga[1576] = VGA_CHAR('-', BLACK, GREEN);
			if (intentos >= 1) {
				vga[1494] = VGA_CHAR('|', BLACK, GREEN);
				vga[1414] = VGA_CHAR('|', BLACK, GREEN);
				vga[1334] = VGA_CHAR('|', BLACK, GREEN);
				if (intentos >= 2) {
					vga[1254] = VGA_CHAR('|', BLACK, GREEN);
					vga[1174] = VGA_CHAR('|', BLACK, GREEN);
					vga[1094] = VGA_CHAR('|', BLACK, GREEN);
					if (intentos >= 3) {
						vga[1014] = VGA_CHAR('|', BLACK, GREEN);
						vga[934] = VGA_CHAR('|', BLACK, GREEN);
						vga[854] = VGA_CHAR('|', BLACK, GREEN);
						vga[855] = VGA_CHAR('/', BLACK, GREEN);
						vga[774] = VGA_CHAR('_', BLACK, GREEN);
						vga[775] = VGA_CHAR('_', BLACK, GREEN);
						vga[776] = VGA_CHAR('_', BLACK, GREEN);
						vga[777] = VGA_CHAR('_', BLACK, GREEN);
						if (intentos >= 4) {
							vga[857] = VGA_CHAR('|', BLACK, GREEN);
							if (intentos >= 5) {
								vga[937] = VGA_CHAR('O', BLACK, GREEN);
								if (intentos >= 6) {
									vga[1016] = VGA_CHAR('-', BLACK, GREEN);
									vga[1017] = VGA_CHAR('-', BLACK, GREEN);
									vga[1018] = VGA_CHAR('-', BLACK, GREEN);
									if (intentos >= 7) {
										vga[1097] = VGA_CHAR('|', BLACK, GREEN);
										if (intentos >= 8) {
											vga[1176] = VGA_CHAR('/', BLACK, GREEN);
											if (intentos >= 9) {
												vga[1178] = VGA_CHAR('\\', BLACK, GREEN);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		for (int i=0; i < 10; i++) {
			vga[1642+i] = VGA_CHAR(fails[i], BLACK, GREEN);
		}
		bar("PULSA [RETURN] PARA SALIR");
		key = getchar();
		if (key == '\b') {
			for (int w=0; w < 128; w++) {
				fails[w] = ' ';
			}
			return 0;
		}
		else {
			for (int i=0; i < strlen(words[n]); i++) {
				if (key == words[n][i]) {
					word[i] = key;
				}
			}
			for (int i=0, tf=0; i < strlen(words[n]); i++) {
				if (key == words[n][i]) {
					tf++;
				}
				if (i == strlen(words[n])-1 && tf == 0 && key != fails[0] && key != fails[1] && key != fails[2] && key != fails[3] && key != fails[4] && key != fails[5] && key != fails[6] && key != fails[7] && key != fails[8] && key != fails[9]) {
					intentos++;
					fails[z] = key;
					z++;
				}
			}
		}
		if (intentos > 10) {
			error("", "             GAME OVER", "");
			intentos=0;
			n = aleatorio();
			if (n > 5) {
				n = n / 2;
			}
			for (int i=0; i <= 127; i++) {
				word[i] = '_';
				fails[i] = ' ';
				z = 0;
			}
		}
		for (int i=0; i < strlen(words[n]) && word[i] != '_'; i++) {
			if (i == strlen(words[n])-1) {
				error("             YOU", "             WIN", "");
				intentos=0;
				n = aleatorio();
				if (n > 5) {
					n = n / 2;
				}
				for (int i=0; i <= 127; i++) {
					word[i] = '_';
					fails[i] = ' ';
					z = 0;
				}
			}
		}
	}

}
