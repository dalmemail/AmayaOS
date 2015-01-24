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
#include <VGA.h>
#include <API/ProcessCtl.h>
#include <Error.h>
#include <Types.h>
#include <MemoryMessage.h>
#include <stdlib.h>
#include <API/PrivExec.h>
#include "wama/wamas.cpp"
#include "pong/pong.cpp"
#include <MemoryMessage.h>
#include <Config.h>

int menu(int argc, char **argv);
int salir();
void memoria();

int main(int argc, char **argv)
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

    for (i=0; i < 36; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    vga[36] = VGA_CHAR('A', BLACK, GREEN);
    vga[37] = VGA_CHAR('m', BLACK, GREEN);
    vga[38] = VGA_CHAR('a', BLACK, GREEN);
    vga[39] = VGA_CHAR('y', BLACK, GREEN);
    vga[40] = VGA_CHAR('a', BLACK, GREEN);
    vga[41] = VGA_CHAR('O', BLACK, GREEN);
    vga[42] = VGA_CHAR('S', BLACK, GREEN);
    for (i=43; i < 80; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    for (i=80; i < 1920; i++) {
      vga[i] = VGA_CHAR(' ', WHITE, WHITE);
    }
    vga[1920] = VGA_CHAR(' ', BROWN, BROWN);
    vga[1921] = VGA_CHAR('M', BLUE, BROWN);
    vga[1922] = VGA_CHAR('e', BLUE, BROWN);
    vga[1923] = VGA_CHAR('n', BLUE, BROWN);
    vga[1924] = VGA_CHAR('u', BLUE, BROWN);
    vga[1925] = VGA_CHAR('(', BLUE, BROWN);
    vga[1926] = VGA_CHAR('M', BLUE, BROWN);
    vga[1927] = VGA_CHAR(')', BLUE, BROWN);
    for (i=1928; i <= 2000; i++) {
      vga[i] = VGA_CHAR(' ', BROWN, BROWN);
    }
    memoria();
    do {
      tecla = getchar();
    } while (tecla != 'M'&& tecla != 'm');
    if (tecla == 'M'|| tecla == 'm') {
      menu(argc, argv);
    }
}

int menu(int argc, char **argv)
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

    for (i=0; i < 36; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    vga[36] = VGA_CHAR('A', BLACK, GREEN);
    vga[37] = VGA_CHAR('m', BLACK, GREEN);
    vga[38] = VGA_CHAR('a', BLACK, GREEN);
    vga[39] = VGA_CHAR('y', BLACK, GREEN);
    vga[40] = VGA_CHAR('a', BLACK, GREEN);
    vga[41] = VGA_CHAR('O', BLACK, GREEN);
    vga[42] = VGA_CHAR('S', BLACK, GREEN);
    for (i=43; i < 80; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    for (i=80; i < 1680; i++) {
      vga[i] = VGA_CHAR(' ', WHITE, WHITE);
    }
/*    vga[1520] = VGA_CHAR('A', BLUE, BROWN);
    vga[1521] = VGA_CHAR('m', BLUE, BROWN);
    vga[1522] = VGA_CHAR('a', BLUE, BROWN);
    vga[1523] = VGA_CHAR('y', BLUE, BROWN);
    vga[1524] = VGA_CHAR('a', BLUE, BROWN);
    vga[1525] = VGA_CHAR('F', BLUE, BROWN);
    vga[1526] = VGA_CHAR('A', BLUE, BROWN);
    vga[1527] = VGA_CHAR('C', BLUE, BROWN);
    vga[1528] = VGA_CHAR('T', BLUE, BROWN);
    vga[1529] = VGA_CHAR('(', BLUE, BROWN);
    vga[1530] = VGA_CHAR('C', BLUE, BROWN);
    vga[1531] = VGA_CHAR(')', BLUE, BROWN);*/
    vga[1600] = VGA_CHAR('P', BLUE, BROWN);
    vga[1601] = VGA_CHAR('o', BLUE, BROWN);
    vga[1602] = VGA_CHAR('n', BLUE, BROWN);
    vga[1603] = VGA_CHAR('g', BLUE, BROWN);
    vga[1604] = VGA_CHAR('(', BLUE, BROWN);
    vga[1605] = VGA_CHAR('P', BLUE, BROWN);
    vga[1606] = VGA_CHAR(')', BLUE, BROWN);
    for (i=1607; i <= 1611; i++) {
	vga[i] = VGA_CHAR(' ', BLUE, BROWN);
    }
    vga[1680] = VGA_CHAR('W', BLUE, BROWN);
    vga[1681] = VGA_CHAR('a', BLUE, BROWN);
    vga[1682] = VGA_CHAR('m', BLUE, BROWN);
    vga[1683] = VGA_CHAR('a', BLUE, BROWN);
    vga[1684] = VGA_CHAR('/', BLUE, BROWN);
    vga[1685] = VGA_CHAR('W', BLUE, BROWN);
    vga[1686] = VGA_CHAR('A', BLUE, BROWN);
    vga[1687] = VGA_CHAR('+', BLUE, BROWN);
    vga[1688] = VGA_CHAR('(', BLUE, BROWN);
    vga[1689] = VGA_CHAR('W', BLUE, BROWN);
    vga[1690] = VGA_CHAR(')', BLUE, BROWN);
    vga[1691] = VGA_CHAR(' ', BLUE, BROWN);
    for (i=1692; i < 1760; i++) {
      vga[i] = VGA_CHAR(' ', WHITE, WHITE);
    }
    vga[1760] = VGA_CHAR('R', BLUE, BROWN);
    vga[1761] = VGA_CHAR('e', BLUE, BROWN);
    vga[1762] = VGA_CHAR('i', BLUE, BROWN);
    vga[1763] = VGA_CHAR('n', BLUE, BROWN);
    vga[1764] = VGA_CHAR('i', BLUE, BROWN);
    vga[1765] = VGA_CHAR('c', BLUE, BROWN);
    vga[1766] = VGA_CHAR('i', BLUE, BROWN);
    vga[1767] = VGA_CHAR('a', BLUE, BROWN);
    vga[1768] = VGA_CHAR('r', BLUE, BROWN);
    vga[1769] = VGA_CHAR('(', BLUE, BROWN);
    vga[1770] = VGA_CHAR('R', BLUE, BROWN);
    vga[1771] = VGA_CHAR(')', BLUE, BROWN);
    for (i=1772; i < 1840; i++) {
      vga[i] = VGA_CHAR(' ', WHITE, WHITE);
    }
    vga[1840] = VGA_CHAR('S', BLUE, BROWN);
    vga[1841] = VGA_CHAR('h', BLUE, BROWN);
    vga[1842] = VGA_CHAR('e', BLUE, BROWN);
    vga[1843] = VGA_CHAR('l', BLUE, BROWN);
    vga[1844] = VGA_CHAR('l', BLUE, BROWN);
    vga[1845] = VGA_CHAR('(', BLUE, BROWN);
    vga[1846] = VGA_CHAR('S', BLUE, BROWN);
    vga[1847] = VGA_CHAR(')', BLUE, BROWN);
    vga[1848] = VGA_CHAR(' ', BLUE, BROWN);
    vga[1849] = VGA_CHAR(' ', BLUE, BROWN);
    vga[1850] = VGA_CHAR(' ', BLUE, BROWN);
    vga[1851] = VGA_CHAR(' ', BLUE, BROWN);
    memoria();
    do {
      tecla = getchar();
    } while (tecla != 'R'&& tecla != 'r'&& tecla != 'S'&& tecla != 's'&& 'M'&& tecla != 'm'&& tecla != 'W'&& tecla != 'w'
             &&tecla != 'P'&& tecla != 'p');
    if (tecla == 'M'|| tecla == 'm') {
      main(argc, argv);
    }
    if (tecla == 'R'|| tecla == 'r') {
      return PrivExec(Reboot);
    }
    if (tecla == 'S'|| tecla == 's') {
      salir();
    }
    if (tecla == 'W'|| tecla == 'w') {
      wama();
    }
    if (tecla == 'P'|| tecla == 'p') {
      game();
    }

    return 0;
}

int salir()
{
    char clean[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
    printf("%s", clean);
    return 0;
}

void memoria()
{
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

    /* Obtenemos el uso de la memoria. */
    mem.action = SystemMemory;
    mem.ipc(MEMSRV_PID, SendReceive, sizeof(mem));
    for (i=209; i <= 239; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    vga[211] = VGA_CHAR('E', BLACK, GREEN);
    vga[212] = VGA_CHAR('s', BLACK, GREEN);
    vga[213] = VGA_CHAR('t', BLACK, GREEN);
    vga[214] = VGA_CHAR('a', BLACK, GREEN);
    vga[215] = VGA_CHAR('d', BLACK, GREEN);
    vga[216] = VGA_CHAR('o', BLACK, GREEN);
    vga[217] = VGA_CHAR(' ', BLACK, GREEN);
    vga[218] = VGA_CHAR('d', BLACK, GREEN);
    vga[219] = VGA_CHAR('e', BLACK, GREEN);
    vga[220] = VGA_CHAR(' ', BLACK, GREEN);
    vga[221] = VGA_CHAR('l', BLACK, GREEN);
    vga[222] = VGA_CHAR('a', BLACK, GREEN);
    vga[223] = VGA_CHAR(' ', BLACK, GREEN);
    vga[224] = VGA_CHAR('m', BLACK, GREEN);
    vga[225] = VGA_CHAR('e', BLACK, GREEN);
    vga[226] = VGA_CHAR('m', BLACK, GREEN);
    vga[227] = VGA_CHAR('o', BLACK, GREEN);
    vga[228] = VGA_CHAR('r', BLACK, GREEN);
    vga[229] = VGA_CHAR('i', BLACK, GREEN);
    vga[230] = VGA_CHAR('a', BLACK, GREEN);
    vga[289] = VGA_CHAR(' ', GREEN, GREEN);
    vga[319] = VGA_CHAR(' ', GREEN, GREEN);
    vga[369] = VGA_CHAR(' ', GREEN, GREEN);
    vga[399] = VGA_CHAR(' ', GREEN, GREEN);
    vga[449] = VGA_CHAR(' ', GREEN, GREEN);
    vga[479] = VGA_CHAR(' ', GREEN, GREEN);
    for (i=529; i <= 559; i++) {
      vga[i] = VGA_CHAR(' ', GREEN, GREEN);
    }
    vga[290] = VGA_CHAR('T', BLACK, WHITE);
    vga[291] = VGA_CHAR('o', BLACK, WHITE);
    vga[292] = VGA_CHAR('t', BLACK, WHITE);
    vga[293] = VGA_CHAR('a', BLACK, WHITE);
    vga[294] = VGA_CHAR('l', BLACK, WHITE);
    vga[295] = VGA_CHAR(':', BLACK, WHITE);
    int a=mem.bytes / 1024;
    char a2[25];
    itoa(a2, 10, a);
    vga[297] = VGA_CHAR(a2[0], BLACK, WHITE);
    vga[298] = VGA_CHAR(a2[1], BLACK, WHITE);
    vga[299] = VGA_CHAR(a2[2], BLACK, WHITE);
    vga[300] = VGA_CHAR(a2[3], BLACK, WHITE);
    vga[301] = VGA_CHAR(a2[4], BLACK, WHITE);
    vga[302] = VGA_CHAR(a2[5], BLACK, WHITE);
    vga[303] = VGA_CHAR(a2[6], BLACK, WHITE);
    vga[304] = VGA_CHAR(a2[7], BLACK, WHITE);
    vga[305] = VGA_CHAR(a2[8], BLACK, WHITE);
    vga[306] = VGA_CHAR('K', BLACK, WHITE);
    vga[307] = VGA_CHAR('i', BLACK, WHITE);
    vga[308] = VGA_CHAR('B', BLACK, WHITE);
    vga[370] = VGA_CHAR('D', BLACK, WHITE);
    vga[371] = VGA_CHAR('i', BLACK, WHITE);
    vga[372] = VGA_CHAR('s', BLACK, WHITE);
    vga[373] = VGA_CHAR('p', BLACK, WHITE);
    vga[374] = VGA_CHAR('o', BLACK, WHITE);
    vga[375] = VGA_CHAR('n', BLACK, WHITE);
    vga[376] = VGA_CHAR('i', BLACK, WHITE);
    vga[377] = VGA_CHAR('b', BLACK, WHITE);
    vga[378] = VGA_CHAR('l', BLACK, WHITE);
    vga[379] = VGA_CHAR('e', BLACK, WHITE);
    vga[380] = VGA_CHAR(':', BLACK, WHITE);
    int b=mem.free / 1024;
    char b2[25];
    itoa(b2, 10, b);
    vga[381] = VGA_CHAR(b2[0], BLACK, WHITE);
    vga[382] = VGA_CHAR(b2[1], BLACK, WHITE);
    vga[383] = VGA_CHAR(b2[2], BLACK, WHITE);
    vga[384] = VGA_CHAR(b2[3], BLACK, WHITE);
    vga[385] = VGA_CHAR(b2[4], BLACK, WHITE);
    vga[386] = VGA_CHAR(b2[5], BLACK, WHITE);
    vga[387] = VGA_CHAR(b2[6], BLACK, WHITE);
    vga[388] = VGA_CHAR(b2[7], BLACK, WHITE);
    vga[389] = VGA_CHAR(b2[8], BLACK, WHITE);
    vga[390] = VGA_CHAR('K', BLACK, WHITE);
    vga[391] = VGA_CHAR('i', BLACK, WHITE);
    vga[392] = VGA_CHAR('B', BLACK, WHITE);
    vga[450] = VGA_CHAR('E', BLACK, WHITE);
    vga[451] = VGA_CHAR('n', BLACK, WHITE);
    vga[452] = VGA_CHAR(' ', BLACK, WHITE);
    vga[453] = VGA_CHAR('U', BLACK, WHITE);
    vga[454] = VGA_CHAR('s', BLACK, WHITE);
    vga[455] = VGA_CHAR('o', BLACK, WHITE);
    vga[456] = VGA_CHAR(':', BLACK, WHITE);
    int c=(mem.bytes - mem.free) / 1024;
    char c2[25];
    itoa(c2, 10, c);
    vga[458] = VGA_CHAR(c2[0], BLACK, WHITE);
    vga[459] = VGA_CHAR(c2[1], BLACK, WHITE);
    vga[460] = VGA_CHAR(c2[2], BLACK, WHITE);
    vga[461] = VGA_CHAR(c2[3], BLACK, WHITE);
    vga[462] = VGA_CHAR(c2[4], BLACK, WHITE);
    vga[463] = VGA_CHAR(c2[5], BLACK, WHITE);
    vga[464] = VGA_CHAR(c2[6], BLACK, WHITE);
    vga[465] = VGA_CHAR(c2[7], BLACK, WHITE);
    vga[466] = VGA_CHAR(c2[8], BLACK, WHITE);
    vga[467] = VGA_CHAR('K', BLACK, WHITE);
    vga[468] = VGA_CHAR('i', BLACK, WHITE);
    vga[469] = VGA_CHAR('B', BLACK, WHITE);
}
