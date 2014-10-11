/*
 * Copyright (C) 2014 Dan Rulos
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
//#include "game/game.cpp"
#include "AmayaCALC/AmayaCALC.cpp"

int menu(int argc, char **argv);
int salir();

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
      vga[i] = VGA_CHAR(' ', BLUE, BLUE);
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
      vga[i] = VGA_CHAR(' ', BLUE, BLUE);
    }
    vga[1520] = VGA_CHAR('A', BLUE, BROWN);
    vga[1521] = VGA_CHAR('m', BLUE, BROWN);
    vga[1522] = VGA_CHAR('a', BLUE, BROWN);
    vga[1523] = VGA_CHAR('y', BLUE, BROWN);
    vga[1524] = VGA_CHAR('a', BLUE, BROWN);
    vga[1525] = VGA_CHAR('C', BLUE, BROWN);
    vga[1526] = VGA_CHAR('A', BLUE, BROWN);
    vga[1527] = VGA_CHAR('L', BLUE, BROWN);
    vga[1528] = VGA_CHAR('C', BLUE, BROWN);
    vga[1529] = VGA_CHAR('(', BLUE, BROWN);
    vga[1530] = VGA_CHAR('C', BLUE, BROWN);
    vga[1531] = VGA_CHAR(')', BLUE, BROWN);
    vga[1600] = VGA_CHAR(' ', BLUE, BROWN);
    vga[1601] = VGA_CHAR('C', BLUE, BROWN);
    vga[1602] = VGA_CHAR('A', BLUE, BROWN);
    vga[1603] = VGA_CHAR('L', BLUE, BROWN);
    vga[1604] = VGA_CHAR('C', BLUE, BROWN);
    vga[1605] = VGA_CHAR('(', BLUE, BROWN);
    vga[1606] = VGA_CHAR('C', BLUE, BROWN);
    vga[1607] = VGA_CHAR(')', BLUE, BROWN);
    vga[1608] = VGA_CHAR(' ', BLUE, BROWN);
    vga[1609] = VGA_CHAR(' ', BLUE, BROWN);
    vga[1610] = VGA_CHAR(' ', BLUE, BROWN);
    vga[1611] = VGA_CHAR(' ', BLUE, BROWN);
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
      vga[i] = VGA_CHAR(' ', BLUE, BLUE);
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
      vga[i] = VGA_CHAR(' ', BLUE, BLUE);
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
    do {
      tecla = getchar();
    } while (tecla != 'R'&& tecla != 'r'&& tecla != 'S'&& tecla != 's'&& 'M'&& tecla != 'm'&& tecla != 'W'&& tecla != 'w'
             &&tecla != 'C'&& tecla != 'c');
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
    if (tecla == 'C'|| tecla == 'c') {
      amayacalc();
    }
}

int salir()
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

    for (i=0; i < 2000; i++) {
      vga[i] = VGA_CHAR(' ', BLACK, BLACK);
    }
    return EXIT_SUCCESS;
}
