/*
# Copyright (C) 2014 Team Espartano (AmayaOS), 2015 Dan Rulos (AmayaOS).
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <files.h>
 
int ver2(char *contenido);

int errorlectura()
{
    char tecla;
    int i;
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

    for (i=0; i < 821; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    for (i=821; i < 861; i++) {
      vga[i] = VGA_CHAR(' ', BLACK, RED);
    }
    for (i=861; i < 901; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
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
    for (i=941; i < 981; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
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
    for (i=1021; i < 1061; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
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
    for (i=1101; i < 2000; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    do {
      tecla = getchar();
    } while (tecla != 'A'&& tecla != 'a');
    if (tecla == 'a'|| tecla == 'A') {
      return -1;
    }
    return -1;
}

void reader(char *archivo)
{
    int fd;
    if ((fd = open(archivo, O_RDONLY)) < 0) {
      errorlectura();
    }
    close(fd);
    /* Intentamos mostrar el contenido. */
    file *fichero = new file();
    fichero->setpath(archivo);
    fichero->f_open(O_RDONLY);
    char *contenido = fichero->readAll();
    fichero->f_close();
    ver2(contenido);
}

int ver2(char *contenido)
{
    int i;
    char tecla;
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
    char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
    printf("%s\n", str);
    printf("%s", contenido);
    for (i=0; i < 36; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    vga[36] = VGA_CHAR('W', BLACK, GREEN);
    vga[37] = VGA_CHAR('A', BLACK, GREEN);
    vga[38] = VGA_CHAR('M', BLACK, GREEN);
    vga[39] = VGA_CHAR('A', BLACK, GREEN);
    vga[40] = VGA_CHAR(' ', BLACK, GREEN);
    vga[41] = VGA_CHAR('0', BLACK, GREEN);
    vga[42] = VGA_CHAR('.', BLACK, GREEN);
    vga[43] = VGA_CHAR('2', BLACK, GREEN);
    for (i=44; i < 80; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    vga[1920] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1921] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1922] = VGA_CHAR('[', BLACK, BROWN);
    vga[1923] = VGA_CHAR('A', BLACK, BROWN);
    vga[1924] = VGA_CHAR(']', BLACK, BROWN);
    vga[1925] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1926] = VGA_CHAR('A', BLACK, BROWN);
    vga[1927] = VGA_CHAR('c', BLACK, BROWN);
    vga[1928] = VGA_CHAR('e', BLACK, BROWN);
    vga[1929] = VGA_CHAR('p', BLACK, BROWN);
    vga[1930] = VGA_CHAR('t', BLACK, BROWN);
    vga[1931] = VGA_CHAR('a', BLACK, BROWN);
    vga[1932] = VGA_CHAR('r', BLACK, BROWN);
    for (i=1933; i < 2000; i++) {
      vga[i] = VGA_CHAR(' ', BROWN, BROWN);
    }
    do {
      tecla = getchar();
    } while (tecla != 'A'&& tecla != 'a');
    if (tecla == 'A'|| tecla == 'A') {
      return 0;
    }
    return 0;
}
