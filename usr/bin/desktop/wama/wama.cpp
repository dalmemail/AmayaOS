/*
 * Copyright (C) 2015 Dan Rulos [amaya@amayaos.com]
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

#include <VGA.h>
#include <stdio.h>
#include <stdlib.h>
#include <files.h>
#include "wama.h"

u16 *vga;
MemoryMessage mem;

void setwindow()
{
	/* Request VGA memory. */
	mem.action    = CreatePrivate;
	mem.bytes     = PAGESIZE;
	mem.virtualAddress  = ZERO;
	mem.physicalAddress = VGA_PADDR;
	mem.protection      = PAGE_RW | PAGE_PINNED;
	mem.ipc(MEMSRV_PID, SendReceive, sizeof(mem));

	/* Point to the VGA mapping. */
	vga = (u16 *) mem.virtualAddress;
	for (int i = 0; i < 80; i++) {
		vga[i] = VGA_CHAR(' ', GREEN, GREEN);
	}
	vga[36] = VGA_CHAR('W', BLACK, GREEN);
	vga[37] = VGA_CHAR('A', BLACK, GREEN);
	vga[38] = VGA_CHAR('M', BLACK, GREEN);
	vga[39] = VGA_CHAR('A', BLACK, GREEN);
	vga[41] = VGA_CHAR('0', BLACK, GREEN);
	vga[42] = VGA_CHAR('.', BLACK, GREEN);
	vga[43] = VGA_CHAR('5', BLACK, GREEN);
}

void setscreenblue()
{
	/* Request VGA memory. */
	mem.action    = CreatePrivate;
	mem.bytes     = PAGESIZE;
	mem.virtualAddress  = ZERO;
	mem.physicalAddress = VGA_PADDR;
	mem.protection      = PAGE_RW | PAGE_PINNED;
	mem.ipc(MEMSRV_PID, SendReceive, sizeof(mem));

	/* Point to the VGA mapping. */
	vga = (u16 *) mem.virtualAddress;
	for (int i = 0; i < 2000; i++) {
		vga[i] = VGA_CHAR(' ', BLUE, BLUE);
	}
}

void setoption()
{
	/* Request VGA memory. */
	mem.action    = CreatePrivate;
	mem.bytes     = PAGESIZE;
	mem.virtualAddress  = ZERO;
	mem.physicalAddress = VGA_PADDR;
	mem.protection      = PAGE_RW | PAGE_PINNED;
	mem.ipc(MEMSRV_PID, SendReceive, sizeof(mem));

	/* Point to the VGA mapping. */
	vga = (u16 *) mem.virtualAddress;
	for (int i = 1920; i < 2000; i++) {
		vga[i] = VGA_CHAR(' ', BROWN, BROWN);
	}
	char *menu[4];
	menu[0] = "[V]er Archivo";
	menu[1] = "[N]uevo Archivo";
	menu[2] = "[E]ditar Archivo";
	menu[3] = "[S]alir";
	int y = 1921;
	for (int i = 0; i < 4; i++) {
		for (unsigned int x = 0; x < strlen(menu[i]); x++) {
			vga[y] = VGA_CHAR(menu[i][x], BLACK, BROWN);
			y++;
		}
		vga[y] = VGA_CHAR(' ', BLACK, BROWN);
		y++;
	}
}

void clean_screen()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

void error()
{
	int i;
	/* Request VGA memory. */
	mem.action    = CreatePrivate;
	mem.bytes     = PAGESIZE;
	mem.virtualAddress  = ZERO;
	mem.physicalAddress = VGA_PADDR;
	mem.protection      = PAGE_RW | PAGE_PINNED;
	mem.ipc(MEMSRV_PID, SendReceive, sizeof(mem));

	/* Point to the VGA mapping. */
	vga = (u16 *) mem.virtualAddress;

 	for (i=0; i < 2000; i++) {
		vga[i] = VGA_CHAR(' ', GREEN, GREEN);
	}
	for (i=821; i < 861; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	for (i=901; i < 920; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	vga[920] = VGA_CHAR('E', BLACK, RED);
	vga[921] = VGA_CHAR('R', BLACK, RED);
	vga[922] = VGA_CHAR('R', BLACK, RED);
	vga[923] = VGA_CHAR('O', BLACK, RED);
	vga[924] = VGA_CHAR('R', BLACK, RED);
	for (i=925; i < 941; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	for (i=981; i < 991; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	vga[991] = VGA_CHAR(' ', BLACK, RED);
	vga[992] = VGA_CHAR(' ', BLACK, RED);
	vga[993] = VGA_CHAR('A', BLACK, RED);
	vga[994] = VGA_CHAR('l', BLACK, RED);
	vga[995] = VGA_CHAR(' ', BLACK, RED);
	vga[996] = VGA_CHAR('a', BLACK, RED);
	vga[997] = VGA_CHAR('b', BLACK, RED);
	vga[998] = VGA_CHAR('r', BLACK, RED);
	vga[999] = VGA_CHAR('i', BLACK, RED);
	vga[1000] = VGA_CHAR('r', BLACK, RED);
	vga[1001] = VGA_CHAR(' ', BLACK, RED);
	vga[1002] = VGA_CHAR('e', BLACK, RED);
	vga[1003] = VGA_CHAR('l', BLACK, RED);
	vga[1004] = VGA_CHAR(' ', BLACK, RED);
	vga[1005] = VGA_CHAR('a', BLACK, RED);
	vga[1006] = VGA_CHAR('r', BLACK, RED);
	vga[1007] = VGA_CHAR('c', BLACK, RED);
	vga[1008] = VGA_CHAR('h', BLACK, RED);
	vga[1009] = VGA_CHAR('i', BLACK, RED);
	vga[1010] = VGA_CHAR('v', BLACK, RED);
	vga[1011] = VGA_CHAR('o', BLACK, RED);
	for (i=1012; i < 1021; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	for (i=1061; i < 1076; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	vga[1076] = VGA_CHAR('A', BLACK, RED);
	vga[1077] = VGA_CHAR('c', BLACK, RED);
	vga[1078] = VGA_CHAR('e', BLACK, RED);
	vga[1079] = VGA_CHAR('p', BLACK, RED);
	vga[1080] = VGA_CHAR('t', BLACK, RED);
	vga[1081] = VGA_CHAR('a', BLACK, RED);
	vga[1082] = VGA_CHAR('r', BLACK, RED);
	vga[1083] = VGA_CHAR('(', BLACK, RED);
	vga[1084] = VGA_CHAR('A', BLACK, RED);
	vga[1085] = VGA_CHAR(')', BLACK, RED);
	for (i=1086; i < 1101; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	do {
	} while (getchar() != 'a');
}

void save()
{
	int i;
	/* Request VGA memory. */
	mem.action    = CreatePrivate;
	mem.bytes     = PAGESIZE;
	mem.virtualAddress  = ZERO;
	mem.physicalAddress = VGA_PADDR;
	mem.protection      = PAGE_RW | PAGE_PINNED;
	mem.ipc(MEMSRV_PID, SendReceive, sizeof(mem));

	/* Point to the VGA mapping. */
	vga = (u16 *) mem.virtualAddress;

	for (i=0; i < 2000; i++) {
		vga[i] = VGA_CHAR(' ', GREEN, GREEN);
	}
	for (i=821; i < 861; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	for (i=901; i < 920; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	vga[920] = VGA_CHAR(' ', BLACK, RED);
	vga[921] = VGA_CHAR(' ', BLACK, RED);
	vga[922] = VGA_CHAR(' ', BLACK, RED);
	vga[923] = VGA_CHAR(' ', BLACK, RED);
	vga[924] = VGA_CHAR(' ', BLACK, RED);
	for (i=925; i < 941; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	for (i=981; i < 991; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	vga[991] = VGA_CHAR(' ', BLACK, RED);
	vga[992] = VGA_CHAR(' ', BLACK, RED);
	vga[993] = VGA_CHAR(' ', BLACK, RED);
	vga[994] = VGA_CHAR(' ', BLACK, RED);
	vga[995] = VGA_CHAR(' ', BLACK, RED);
	vga[996] = VGA_CHAR(' ', BLACK, RED);
	vga[997] = VGA_CHAR(' ', BLACK, RED);
	vga[998] = VGA_CHAR('G', BLACK, RED);
	vga[999] = VGA_CHAR('u', BLACK, RED);
	vga[1000] = VGA_CHAR('a', BLACK, RED);
	vga[1001] = VGA_CHAR('r', BLACK, RED);
	vga[1002] = VGA_CHAR('d', BLACK, RED);
	vga[1003] = VGA_CHAR('a', BLACK, RED);
	vga[1004] = VGA_CHAR('d', BLACK, RED);
	vga[1005] = VGA_CHAR('o', BLACK, RED);
	vga[1006] = VGA_CHAR(' ', BLACK, RED);
	vga[1007] = VGA_CHAR(' ', BLACK, RED);
	vga[1008] = VGA_CHAR(' ', BLACK, RED);
	vga[1009] = VGA_CHAR(' ', BLACK, RED);
	vga[1010] = VGA_CHAR(' ', BLACK, RED);
	vga[1011] = VGA_CHAR(' ', BLACK, RED);
	for (i=1012; i < 1021; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	for (i=1061; i < 1076; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	vga[1076] = VGA_CHAR('A', BLACK, RED);
	vga[1077] = VGA_CHAR('c', BLACK, RED);
	vga[1078] = VGA_CHAR('e', BLACK, RED);
	vga[1079] = VGA_CHAR('p', BLACK, RED);
	vga[1080] = VGA_CHAR('t', BLACK, RED);
	vga[1081] = VGA_CHAR('a', BLACK, RED);
	vga[1082] = VGA_CHAR('r', BLACK, RED);
	vga[1083] = VGA_CHAR('(', BLACK, RED);
	vga[1084] = VGA_CHAR('A', BLACK, RED);
	vga[1085] = VGA_CHAR(')', BLACK, RED);
	for (i=1086; i < 1101; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	do {
	} while (getchar() != 'a');
}

int checkWamaCommand(char *line)
{
	if ((strcmp(line, "exit")) == 0) {
		return 2;
	}
	if ((strcmp(line, "goto")) == 0) {
		return 1;
	}
	return 0;
}

void subwindow(int n_lines)
{
	int i;
	/* Request VGA memory. */
	mem.action    = CreatePrivate;
	mem.bytes     = PAGESIZE;
	mem.virtualAddress  = ZERO;
	mem.physicalAddress = VGA_PADDR;
	mem.protection      = PAGE_RW | PAGE_PINNED;
	mem.ipc(MEMSRV_PID, SendReceive, sizeof(mem));

	/* Point to the VGA mapping. */
	vga = (u16 *) mem.virtualAddress;
	char lines[3];
	itoa(lines, 10, n_lines);
	for (i = 80; i < 160; i++) {
		vga[i] = VGA_CHAR(' ', BROWN, BROWN);
	}
	unsigned int v=0;
	char *string = "Salir: exit   Editar linea: goto             lineas escritas";
	for (i = 82; v < strlen(string); i++) {
		vga[i] = VGA_CHAR(string[v], BLACK, BROWN);
		v++;
	}
	v=0;
	for (i = 123; v < 3 && lines[v] != '\0'; i++) {
		vga[i] = VGA_CHAR(lines[v], BLACK, BROWN);
		v++;
	}
}

int linecounter(char *c)
{
	int n_lines = 0;
	for (unsigned int i = 0; i < strlen(c); i++) {
		if (c[i] == '\n') {
			n_lines++;
		}
	}
	return n_lines;
}

char *read_file(char *path)
{
	/* Abrimos y leemos el fichero */
	file *fichero = new file();
	fichero->setpath(path);
	fichero->f_open(O_RDONLY);
	char *data = fichero->readAll();
	fichero->f_close();
	/* Devolvemos el contenido del fichero */
	return data;
}

int goto_wama_command(char *path, int line_counter)
{
	char nl[5];
	printf("Numero de linea: ");
	gets_s(nl, 5);
	int nline = atoi(nl);
	/* nline can't be > line_counter */
	if (line_counter == 1 || nline > line_counter) {
		return -1;
	}
	printf("\n %d ", nline);
	char *data = read_file(path);
	int n_lines = linecounter(data);
	char lines[n_lines][128];
	char edit_line[128];
	int i_point = 0;
	int f_point = 0;
	int fd;
	for (int i = 0; i < n_lines; i++) {
		i_point = f_point;
		while (data[f_point] != '\n') {
			f_point++;
		}
		for (int k = 0; (i_point+k) < f_point; k++) {
			lines[i][k] = data[(i_point+k)];
		}
		f_point++;
	}
	gets_s(edit_line, 128);
	strcpy(lines[(nline-1)], edit_line);
	if ((fd = open(path, O_WRONLY)) < 0) {
		return -1;
	}
	for (int i = 0; i < n_lines; i++) {
		write(fd, lines[i], strlen(lines[i]));
		write(fd, "\n", 1);
	}
	printf("\n");
	close(fd);
	return 0;
}
