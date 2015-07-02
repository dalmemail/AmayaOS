/* Wa+ junglaCODE.org Villagran-Cortazar Guanajuato  */
/* @utores: Fernando{fercho} Juan Luis {monolinux} 
  email: developer@junglacode.org  web: www.junglacode.org*/
/* Copyright (C) 2014 Team Espartano (AmayaOS) */
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
along with this program. If not, see <http://www.gnu.org/licenses/> */

#include <stdio.h>
#include <stdlib.h>
#include "reader.cpp"
#include "written.cpp"
#include <VGA.h>

int ver();
int info();
int editar();

int wama()
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

    for (i=0; i < 2000; i++) {
      vga[i] = VGA_CHAR(' ', BLUE, BLUE);
    }

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
    vga[1921] = VGA_CHAR('[', BLACK, BROWN);
    vga[1922] = VGA_CHAR('V', BLACK, BROWN);
    vga[1923] = VGA_CHAR(']', BLACK, BROWN);
    vga[1924] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1925] = VGA_CHAR('V', BLACK, BROWN);
    vga[1926] = VGA_CHAR('e', BLACK, BROWN);
    vga[1927] = VGA_CHAR('r', BLACK, BROWN);
    vga[1928] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1929] = VGA_CHAR('a', BLACK, BROWN);
    vga[1930] = VGA_CHAR('r', BLACK, BROWN);
    vga[1931] = VGA_CHAR('c', BLACK, BROWN);
    vga[1932] = VGA_CHAR('h', BLACK, BROWN);
    vga[1933] = VGA_CHAR('i', BLACK, BROWN);
    vga[1934] = VGA_CHAR('v', BLACK, BROWN);
    vga[1935] = VGA_CHAR('o', BLACK, BROWN);
    vga[1936] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1937] = VGA_CHAR('[', BLACK, BROWN);
    vga[1938] = VGA_CHAR('N', BLACK, BROWN);
    vga[1939] = VGA_CHAR(']', BLACK, BROWN);
    vga[1940] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1941] = VGA_CHAR('N', BLACK, BROWN);
    vga[1942] = VGA_CHAR('u', BLACK, BROWN);
    vga[1943] = VGA_CHAR('e', BLACK, BROWN);
    vga[1944] = VGA_CHAR('v', BLACK, BROWN);
    vga[1945] = VGA_CHAR('o', BLACK, BROWN);
    vga[1946] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1947] = VGA_CHAR('a', BLACK, BROWN);
    vga[1948] = VGA_CHAR('r', BLACK, BROWN);
    vga[1949] = VGA_CHAR('c', BLACK, BROWN);
    vga[1950] = VGA_CHAR('h', BLACK, BROWN);
    vga[1951] = VGA_CHAR('i', BLACK, BROWN);
    vga[1952] = VGA_CHAR('v', BLACK, BROWN);
    vga[1953] = VGA_CHAR('o', BLACK, BROWN);
    vga[1954] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1955] = VGA_CHAR('[', BLACK, BROWN);
    vga[1956] = VGA_CHAR('E', BLACK, BROWN);
    vga[1957] = VGA_CHAR(']', BLACK, BROWN);
    vga[1958] = VGA_CHAR('d', BLACK, BROWN);
    vga[1959] = VGA_CHAR('i', BLACK, BROWN);
    vga[1960] = VGA_CHAR('t', BLACK, BROWN);
    vga[1961] = VGA_CHAR('a', BLACK, BROWN);
    vga[1962] = VGA_CHAR('r', BLACK, BROWN);
    vga[1963] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1964] = VGA_CHAR('a', BLACK, BROWN);
    vga[1965] = VGA_CHAR('r', BLACK, BROWN);
    vga[1966] = VGA_CHAR('c', BLACK, BROWN);
    vga[1967] = VGA_CHAR('h', BLACK, BROWN);
    vga[1968] = VGA_CHAR('i', BLACK, BROWN);
    vga[1969] = VGA_CHAR('v', BLACK, BROWN);
    vga[1970] = VGA_CHAR('o', BLACK, BROWN);
    vga[1971] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1972] = VGA_CHAR('[', BLACK, BROWN);
    vga[1973] = VGA_CHAR('S', BLACK, BROWN);
    vga[1974] = VGA_CHAR(']', BLACK, BROWN);
    vga[1975] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1976] = VGA_CHAR('S', BLACK, BROWN);
    vga[1977] = VGA_CHAR('a', BLACK, BROWN);
    vga[1978] = VGA_CHAR('l', BLACK, BROWN);
    vga[1979] = VGA_CHAR('i', BLACK, BROWN);
    vga[1980] = VGA_CHAR('r', BLACK, BROWN);
    vga[1981] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1982] = VGA_CHAR('[', BLACK, BROWN);
    vga[1983] = VGA_CHAR('I', BLACK, BROWN);
    vga[1984] = VGA_CHAR(']', BLACK, BROWN);
    vga[1985] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1986] = VGA_CHAR('I', BLACK, BROWN);
    vga[1987] = VGA_CHAR('n', BLACK, BROWN);
    vga[1988] = VGA_CHAR('f', BLACK, BROWN);
    vga[1989] = VGA_CHAR('o', BLACK, BROWN);
    for (i=1990; i < 2000; i++) {
      vga[i] = VGA_CHAR(' ', BLACK, BROWN);
    }
    do {
      tecla = getchar();
    } while (tecla != 'V'&& tecla != 'v'&& tecla != 'N'&& tecla != 'n'
             && tecla != 'E'&& tecla != 'e'&& tecla != 'S'&& tecla != 's'&& tecla != 'I'&& tecla != 'i');
    if (tecla == 'S'|| tecla == 's') {
      return 0;
    }
    if (tecla == 'I'|| tecla == 'i') {
      info();
    }
    if (tecla == 'V'|| tecla == 'v') {
      ver();
    }
    if (tecla == 'N'|| tecla == 'n') {
      nuevo();
    }
    if (tecla == 'E'|| tecla == 'e') {
      editar();
    }
    return 0;
}

int info()
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

    for (i=0; i < 2000; i++) {
      vga[i] = VGA_CHAR(' ', BLUE, BLUE);
    }
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
    vga[161] = VGA_CHAR('W', BLACK, BLUE);
    vga[162] = VGA_CHAR('A', BLACK, BLUE);
    vga[163] = VGA_CHAR('M', BLACK, BLUE);
    vga[164] = VGA_CHAR('A', BLACK, BLUE);
    vga[165] = VGA_CHAR(' ', BLACK, BLUE);
    vga[166] = VGA_CHAR('0', BLACK, BLUE);
    vga[167] = VGA_CHAR('.', BLACK, BLUE);
    vga[168] = VGA_CHAR('2', BLACK, BLUE);
    vga[169] = VGA_CHAR(' ', BLACK, BLUE);
    vga[170] = VGA_CHAR('e', BLACK, BLUE);
    vga[171] = VGA_CHAR('s', BLACK, BLUE);
    vga[172] = VGA_CHAR(' ', BLACK, BLUE);
    vga[173] = VGA_CHAR('u', BLACK, BLUE);
    vga[174] = VGA_CHAR('n', BLACK, BLUE);
    vga[175] = VGA_CHAR(' ', BLACK, BLUE);
    vga[176] = VGA_CHAR('e', BLACK, BLUE);
    vga[177] = VGA_CHAR('d', BLACK, BLUE);
    vga[178] = VGA_CHAR('i', BLACK, BLUE);
    vga[179] = VGA_CHAR('t', BLACK, BLUE);
    vga[180] = VGA_CHAR('o', BLACK, BLUE);
    vga[181] = VGA_CHAR('r', BLACK, BLUE);
    vga[182] = VGA_CHAR(' ', BLACK, BLUE);
    vga[183] = VGA_CHAR('d', BLACK, BLUE);
    vga[184] = VGA_CHAR('e', BLACK, BLUE);
    vga[185] = VGA_CHAR(' ', BLACK, BLUE);
    vga[186] = VGA_CHAR('t', BLACK, BLUE);
    vga[187] = VGA_CHAR('e', BLACK, BLUE);
    vga[188] = VGA_CHAR('x', BLACK, BLUE);
    vga[189] = VGA_CHAR('t', BLACK, BLUE);
    vga[190] = VGA_CHAR('o', BLACK, BLUE);
    vga[191] = VGA_CHAR(' ', BLACK, BLUE);
    vga[192] = VGA_CHAR('i', BLACK, BLUE);
    vga[193] = VGA_CHAR('n', BLACK, BLUE);
    vga[194] = VGA_CHAR('s', BLACK, BLUE);
    vga[195] = VGA_CHAR('p', BLACK, BLUE);
    vga[196] = VGA_CHAR('i', BLACK, BLUE);
    vga[197] = VGA_CHAR('r', BLACK, BLUE);
    vga[198] = VGA_CHAR('a', BLACK, BLUE);
    vga[199] = VGA_CHAR('d', BLACK, BLUE);
    vga[200] = VGA_CHAR('o', BLACK, BLUE);
    vga[201] = VGA_CHAR(' ', BLACK, BLUE);
    vga[202] = VGA_CHAR('e', BLACK, BLUE);
    vga[203] = VGA_CHAR('n', BLACK, BLUE);
    vga[204] = VGA_CHAR(' ', BLACK, BLUE);
    vga[205] = VGA_CHAR('G', BLACK, BLUE);
    vga[206] = VGA_CHAR('N', BLACK, BLUE);
    vga[207] = VGA_CHAR('U', BLACK, BLUE);
    vga[208] = VGA_CHAR(' ', BLACK, BLUE);
    vga[209] = VGA_CHAR('E', BLACK, BLUE);
    vga[210] = VGA_CHAR('m', BLACK, BLUE);
    vga[211] = VGA_CHAR('a', BLACK, BLUE);
    vga[212] = VGA_CHAR('c', BLACK, BLUE);
    vga[213] = VGA_CHAR('s', BLACK, BLUE);
    vga[214] = VGA_CHAR('.', BLACK, BLUE);
    vga[215] = VGA_CHAR(' ', BLACK, BLUE);
    vga[216] = VGA_CHAR('L', BLACK, BLUE);
    vga[217] = VGA_CHAR('i', BLACK, BLUE);
    vga[218] = VGA_CHAR('c', BLACK, BLUE);
    vga[219] = VGA_CHAR('e', BLACK, BLUE);
    vga[220] = VGA_CHAR('n', BLACK, BLUE);
    vga[221] = VGA_CHAR('c', BLACK, BLUE);
    vga[222] = VGA_CHAR('i', BLACK, BLUE);
    vga[223] = VGA_CHAR('a', BLACK, BLUE);
    vga[224] = VGA_CHAR(' ', BLACK, BLUE);
    vga[225] = VGA_CHAR('G', BLACK, BLUE);
    vga[226] = VGA_CHAR('N', BLACK, BLUE);
    vga[227] = VGA_CHAR('U', BLACK, BLUE);
    vga[228] = VGA_CHAR(' ', BLACK, BLUE);
    vga[229] = VGA_CHAR('G', BLACK, BLUE);
    vga[230] = VGA_CHAR('P', BLACK, BLUE);
    vga[231] = VGA_CHAR('L', BLACK, BLUE);
    vga[232] = VGA_CHAR(' ', BLACK, BLUE);
    vga[233] = VGA_CHAR('v', BLACK, BLUE);
    vga[234] = VGA_CHAR('3', BLACK, BLUE);
    vga[235] = VGA_CHAR('.', BLACK, BLUE);
    vga[236] = VGA_CHAR(' ', BLACK, BLUE);
    vga[237] = VGA_CHAR(' ', BLACK, BLUE);
    vga[240] = VGA_CHAR('h', BLACK, BLUE);
    vga[241] = VGA_CHAR('t', BLACK, BLUE);
    vga[242] = VGA_CHAR('t', BLACK, BLUE);
    vga[243] = VGA_CHAR('p', BLACK, BLUE);
    vga[244] = VGA_CHAR(':', BLACK, BLUE);
    vga[245] = VGA_CHAR('/', BLACK, BLUE);
    vga[246] = VGA_CHAR('/', BLACK, BLUE);
    vga[247] = VGA_CHAR('g', BLACK, BLUE);
    vga[248] = VGA_CHAR('i', BLACK, BLUE);
    vga[249] = VGA_CHAR('t', BLACK, BLUE);
    vga[250] = VGA_CHAR('l', BLACK, BLUE);
    vga[251] = VGA_CHAR('a', BLACK, BLUE);
    vga[252] = VGA_CHAR('b', BLACK, BLUE);
    vga[253] = VGA_CHAR('.', BLACK, BLUE);
    vga[254] = VGA_CHAR('c', BLACK, BLUE);
    vga[255] = VGA_CHAR('o', BLACK, BLUE);
    vga[256] = VGA_CHAR('m', BLACK, BLUE);
    vga[257] = VGA_CHAR('/', BLACK, BLUE);
    vga[258] = VGA_CHAR('e', BLACK, BLUE);
    vga[259] = VGA_CHAR('q', BLACK, BLUE);
    vga[260] = VGA_CHAR('u', BLACK, BLUE);
    vga[261] = VGA_CHAR('i', BLACK, BLUE);
    vga[262] = VGA_CHAR('p', BLACK, BLUE);
    vga[263] = VGA_CHAR('o', BLACK, BLUE);
    vga[264] = VGA_CHAR('-', BLACK, BLUE);
    vga[265] = VGA_CHAR('e', BLACK, BLUE);
    vga[266] = VGA_CHAR('s', BLACK, BLUE);
    vga[267] = VGA_CHAR('p', BLACK, BLUE);
    vga[268] = VGA_CHAR('a', BLACK, BLUE);
    vga[269] = VGA_CHAR('r', BLACK, BLUE);
    vga[270] = VGA_CHAR('t', BLACK, BLUE);
    vga[271] = VGA_CHAR('a', BLACK, BLUE);
    vga[272] = VGA_CHAR('n', BLACK, BLUE);
    vga[273] = VGA_CHAR('o', BLACK, BLUE);
    vga[274] = VGA_CHAR('/', BLACK, BLUE);
    vga[275] = VGA_CHAR('w', BLACK, BLUE);
    vga[276] = VGA_CHAR('a', BLACK, BLUE);
    vga[277] = VGA_CHAR('m', BLACK, BLUE);
    vga[278] = VGA_CHAR('a', BLACK, BLUE);
    vga[1920] = VGA_CHAR('[', BLACK, BROWN);
    vga[1921] = VGA_CHAR('A', BLACK, BROWN);
    vga[1922] = VGA_CHAR(']', BLACK, BROWN);
    vga[1923] = VGA_CHAR(' ', BLACK, BROWN);
    vga[1924] = VGA_CHAR('A', BLACK, BROWN);
    vga[1925] = VGA_CHAR('c', BLACK, BROWN);
    vga[1926] = VGA_CHAR('e', BLACK, BROWN);
    vga[1927] = VGA_CHAR('p', BLACK, BROWN);
    vga[1928] = VGA_CHAR('t', BLACK, BROWN);
    vga[1929] = VGA_CHAR('a', BLACK, BROWN);
    vga[1930] = VGA_CHAR('r', BLACK, BROWN);
    for (i=1931; i < 2000; i++) {
      vga[i] = VGA_CHAR(' ', BROWN, BROWN);
    }
    do {
      tecla = getchar();
    } while (tecla != 'A'&& tecla != 'a');
    if (tecla == 'A'|| tecla == 'a') {
      wama();
    }
    return i;
}

int ver()
{
//    char *contenido;
    char archivo[128];
    char tecla;
    char ruta[128]="/dev/";
    int i;
//    int idos=0;
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
    printf("Nombre del archivo: ");
    gets(archivo);
    if (archivo[0] == '/') {
      strcpy(ruta, archivo);
    }
    if (archivo[0] != '/') {
      strcat(ruta, archivo);
    }

    for (i=0; i < 2000; i++) {
      vga[i] = VGA_CHAR(' ', BLUE, BLUE);
    }
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
    reader(ruta);
    wama();
//    printf("%s", contenido);
//    getchar();
//    int ica = strlen(contenido);
//    for (i=81; idos < ica ; i++&& idos++) {
//      vga[i] = VGA_CHAR(contenido[idos], BLACK, BLUE);
//    }
    return i;
}

int editar()
{
    char nombre[128];
    char linea[128];
    char ruta[128]="/dev/";
    int i;
    char *newline="\r\n";
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
    printf("Introduce el nombre del archivo a editar: ");
    gets(nombre);
    if (nombre[0] == '/') {
      strcpy(ruta, nombre);
    }
    if (nombre[0] != '/') {
      strcat(ruta, nombre);
    }
    int fd;
    if ((fd = open(ruta, O_RDONLY)) < 0) {
      errorlectura();
    }
    close(fd);
    file *fichero = new file();
    fichero->setpath(ruta);
    fichero->f_open(O_RDONLY);
    char *contenido = fichero->readAll();
    fichero->f_close();
    if ((fd = open(ruta, O_WRONLY)) < 0) {
         errorescritura();
    }
    write(fd, contenido, strlen(contenido));
    char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
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
    printf("%s\r\n", str);
    printf("Escriba exit para salir\r\n");
    do {
      gets(linea);
      if (linea[0] == 'e'&& linea[1] == 'x'&& linea[2] == 'i'&& linea[3] == 't') {
        close(fd);
        infosave();
      }
    write(fd, linea, strlen(linea));
    write(fd, newline, 2);
    } while (linea[0] != 'e'|| linea[1] != 'x'|| linea[2] != 'i'|| linea[3] != 't');
    return 0;
}
