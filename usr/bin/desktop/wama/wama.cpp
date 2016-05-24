/*
 * Copyright (C) 2016 Dan Rulos [amaya@amayaos.com]
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
#include <sys/stat.h>
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
	vga[34] = VGA_CHAR('W', BLACK, GREEN);
	vga[35] = VGA_CHAR('A', BLACK, GREEN);
	vga[36] = VGA_CHAR('M', BLACK, GREEN);
	vga[37] = VGA_CHAR('A', BLACK, GREEN);
	vga[39] = VGA_CHAR('0', BLACK, GREEN);
	vga[40] = VGA_CHAR('.', BLACK, GREEN);
	vga[41] = VGA_CHAR('6', BLACK, GREEN);
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
	for (i=901; i < 941; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	vga[920] = VGA_CHAR('E', BLACK, RED);
	vga[921] = VGA_CHAR('R', BLACK, RED);
	vga[922] = VGA_CHAR('R', BLACK, RED);
	vga[923] = VGA_CHAR('O', BLACK, RED);
	vga[924] = VGA_CHAR('R', BLACK, RED);
	for (i=981; i < 994; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	vga[994] = VGA_CHAR('E', BLACK, RED);
	vga[995] = VGA_CHAR('n', BLACK, RED);
	vga[996] = VGA_CHAR('t', BLACK, RED);
	vga[997] = VGA_CHAR('r', BLACK, RED);
	vga[998] = VGA_CHAR('a', BLACK, RED);
	vga[999] = VGA_CHAR('d', BLACK, RED);
	vga[1000] = VGA_CHAR('a', BLACK, RED);
	vga[1001] = VGA_CHAR(' ', BLACK, RED);
	vga[1002] = VGA_CHAR('o', BLACK, RED);
	vga[1003] = VGA_CHAR(' ', BLACK, RED);
	vga[1004] = VGA_CHAR('S', BLACK, RED);
	vga[1005] = VGA_CHAR('a', BLACK, RED);
	vga[1006] = VGA_CHAR('l', BLACK, RED);
	vga[1007] = VGA_CHAR('i', BLACK, RED);
	vga[1008] = VGA_CHAR('d', BLACK, RED);
	vga[1009] = VGA_CHAR('a', BLACK, RED);
	for (i=1010; i < 1021; i++) {
		vga[i] = VGA_CHAR(' ', BLACK, RED);
	}
	for (i=1061; i < 1101; i++) {
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
	while (getchar() != 'a');
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
	int ret = 0;
	if ((strcmp(line, "$exit")) == 0) {
		ret = 2;
	}
	else if ((strcmp(line, "$nav")) == 0) {
		ret = 1;
	}
	return ret;
}

int linecounter(char *c)
{
	int n_lines = 0;
	int c_len = strlen(c);
	for (int i = 0; i < c_len; i++) {
		if (c[i] == '\n') {
			n_lines++;
		}
	}
	return n_lines;
}

/* prototipo de get_size() */
int get_size(char *path);

char *read_file(char *path)
{
	int file_size = get_size(path);
	char *data = new char [file_size];
	int fd = open(path, O_RDONLY);
	read(fd, data, file_size);
	close(fd);
	/* Devolvemos el contenido del fichero */
	return data;
}

int get_size(char *path)
{
	struct stat st;
	int ssize;
	if ((stat(path, &st)) < 0) {
		ssize = -1;
	}
	else {
		ssize = st.st_size;
	}
	return ssize;
}

char *edit_lines(char *str, size_t size, char *line_to_edit)
{
    char line[1024 + size];
    Size total = 0;
    Size point = 0;
    strcpy(line, line_to_edit);

    printf("%s", line_to_edit);
    total = point = strlen(line_to_edit);

    /* Leemos una linea. */
    while (total < sizeof(line)) {
        /* Leemos un caracter. */
        read(0, line + point, 1);

        /* Procesamos el caracter. */
        switch (line[point]) {
            case '\r':
            case '\n':
                putchar('\n');
                line[total] = ZERO;
                strlcpy(str, line, size);
                return str;

            case '\b':
                if (total > 0) {
                    line[--total] = ZERO;
                    point--;
                    printf("\b \b");
                }
                break;
                
            case '\a':
                /*
                if (point > 0) {
                    printf("\b");
                    point--;
                }
                */
                break;
            default:
                printf("%c", line[point]);
                point++;
                total++;
                break;
        }
    }
    
    line[total] = ZERO;
    
    return line_to_edit;
}

int line_navigator(char *path, int mode)
{
	int ret = 0;
	char *data = read_file(path);
	int n_lines = linecounter(data);
	int act_line = 1;
	char **lines;
	lines = new char *[n_lines];
	lines[0] = &data[0];
	int data_len = strlen(data);
	if (data_len > 0) {
		for (int i = 1, x = 0; data[x] != '\0'; x++) {
			if (data[x] == '\n') {
				data[x] = '\0';
				if (i < n_lines) {
					lines[i] = &data[x+1];
				}
				i++;
			}
		}
		if (n_lines > 1) {
			char char_read[2];
			do {
				clean_screen();
				printf("\n");
				setwindow();
				int start_line = 0;
				if (n_lines >= 20 && act_line >= 20) {
					start_line = (act_line - 20);
				}
				for (int i = start_line; i < (start_line+20) && i < n_lines; i++) {
					printf("\n");
					if (i == (act_line-1)) {
						printf("#");
					}
					else {
						printf(" ");
					}
					printf("%d %s", (i+1), lines[i]);
				}
				read(0, char_read, 1);
				if (char_read[0] == 'w' && act_line < n_lines) {
					act_line++;
				}
				if (char_read[0] == 's' && act_line > 1) {
					act_line--;
				}
			} while(char_read[0] != '\n' && char_read[0] != 'x' && char_read[0] != 'r');
			clean_screen();
			printf("\n\n");
			setwindow();
			if (char_read[0] == '\n' && mode == WRITE_MODE) {
				char edit_line[128];
				printf(" %d ", act_line);
				edit_lines(edit_line, 128, lines[(act_line-1)]);
				lines[act_line-1] = &edit_line[0];
				int fd;
				if ((fd = open(path, O_WRONLY)) < 0) {
					ret = -1;
				}
				else {
					int bytes_wrote = 0;
					for (int i = 0; i < n_lines; i++) {
						int strlen_ = strlen(lines[i]);
						write(fd, lines[i], strlen_);
						bytes_wrote += strlen_;
						write(fd, "\n", 1);
					}
					int size = get_size(path);
					if (bytes_wrote < size) {
						while (bytes_wrote++ < size) {
							write(fd, "\0", 1);
						}
					}
				}
			}
			if (char_read[0] == 'r' && mode == WRITE_MODE) {
				clean_screen();
				printf("Pulse 's' para borrar la linea %d\n", act_line);
				if (getchar() == 's') {
					int fd;
					if ((fd = open(path, O_WRONLY)) < 0) {
						ret = -1;
					}
					else {
						int bytes_wrote = 0;
						for (int i = 0; i < n_lines; i++) {
							if (i != (act_line-1)) {
								int strlen_ = strlen(lines[i]);
								write(fd, lines[i], strlen_);
								bytes_wrote += strlen_;
								write(fd, "\n", 1);
							}
						}
						int size = get_size(path);
						if (bytes_wrote < size) {
							while (bytes_wrote++ < size) {
								write(fd, "\0", 1);
							}
						}
					}
				}
				clean_screen();
				printf("\n\n");
				setwindow();
			}
		}
	}
	delete lines;
	delete data;
	return ret;
}
