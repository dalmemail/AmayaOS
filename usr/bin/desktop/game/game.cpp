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
#include <amaya.h>
#include "error2.cpp"

bool fin(int p, int ia1, int ia2, int ia3, int ia4, int ia5);

int game()
{
    int i;
    int p=1918;
    char tecla;
    int ia1=1500;
    int ia2=1400;
    int ia3=1300;
    int ia4=1700;
    int ia5=1600;
    error2("Amaya Scape v0.1", "Pulsa A para jugar", "Pulsa B para ver los controles");
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
      for (i=0; i < 80; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=162; i < 240; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=1920; i < 2000; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=0; i < 1921; i=i+80) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=79; i < 2000; i=i+80) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=1762; i < 1838; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=1601; i < 1680; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=1442; i < 1520; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=1280; i < 1358; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=1122; i < 1200; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=962; i < 1040; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=800; i < 878; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=642; i < 720; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=480; i < 558; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      for (i=322; i < 400; i++) {
        vga[i] = VGA_CHAR('*', LIGHTBROWN, BLACK);
      }
      vga[1654] = VGA_CHAR(' ', BLACK, BLACK);
      vga[159] = VGA_CHAR('*', BROWN, BLACK);
      vga[p] = VGA_CHAR('*', GREEN, BLACK);
      vga[ia1] = VGA_CHAR('*', WHITE, BLACK);
      vga[ia2] = VGA_CHAR('*', WHITE, BLACK);
      vga[ia3] = VGA_CHAR('*', WHITE, BLACK);
      vga[ia4] = VGA_CHAR('*', WHITE, BLACK);
      vga[ia5] = VGA_CHAR('*', WHITE, BLACK);
//      usleep(1);
      tecla = getchar();
      if (tecla == '%') {
        if (p-80 > 80) { 
          p=p-80;
        }
        if (p-80 < 80) {
        }
        if (p > 161&& p < 240) {
          p=p+80;
        }
        if (p > 1761&& p < 1838) {
          p=p+80;
        }
        if (p > 1600&& p < 1654) {
          p=p+80;
        }
        if (p > 1654&& p < 1680) {
          p=p+80;
        }
        if (p > 1441&& p < 1520) {
          p=p+80;
        }
        if (p > 1280&& p < 1358) {
          p=p+80;
        }
        if (p > 1122&& p < 1200) {
          p=p+80;
        }
        if (p > 962&& p < 1040) {
          p=p+80;
        }
        if (p > 800&& p < 878) {
          p=p+80;
        }
        if (p > 642&& p < 720) {
          p=p+80;
        }
        if (p > 480&& p < 558) {
          p=p+80;
        }
        if (p > 322&& p < 400) {
          p=p+80;
        }
        if (ia1 >= 1920) {
          ia1--;
        }
        if (ia1 < 1920) {
          ia1++;
        }
        if (ia2 <= 80) {
          ia2++;
        }
        if (ia2 > 80) {
          ia2--;
        }
        ia3=ia3+80;
        if (ia3 >= 1920) {
          ia3=ia3-80;
          ia3=ia3-80;
        }
        ia4=ia4-80;
        if (ia4 <= 80) {
          ia4=ia4+80;
          ia4=ia4+80;
        }
        if (ia5 <= 1920) {
          ia5++;
        }
      }
      if (tecla == 'N') {
        if (p+80 < 1920) { 
          p=p+80;
        }
        if (p+80 > 1920) {
        }
        if (p > 161&& p < 240) {
          p=p-80;
        }
        if (p > 1761&& p < 1838) {
          p=p-80;
        }
        if (p > 1600&& p < 1654) {
          p=p-80;
        }
        if (p > 1654&& p < 1680) {
          p=p-80;
        }
        if (p > 1441&& p < 1520) {
          p=p-80;
        }
        if (p > 1280&& p < 1358) {
          p=p-80;
        }
        if (p > 1122&& p < 1200) {
          p=p-80;
        }
        if (p > 962&& p < 1040) {
          p=p-80;
        }
        if (p > 800&& p < 878) {
          p=p-80;
        }
        if (p > 642&& p < 720) {
          p=p-80;
        }
        if (p > 480&& p < 558) {
          p=p-80;
        }
        if (p > 322&& p < 400) {
          p=p-80;
        }
        if (ia1 <= 80) {
          ia1++;
        }
        if (ia1 > 80) {
          ia1--;
        }
        ia2=ia2+80;
        if (ia2 >= 1920) {
          ia2=ia2-80;
          ia2=ia2-80;
        }
        if (ia3 < 1920) {
          ia3++;
        }
        ia4=ia4-80;
        if (ia4 <= 80) {
          ia4=ia4+80;
          ia4=ia4+80;
        }
        ia5=ia5+80;
        if (ia5 >= 1920) {
          ia5=ia5-80;
          ia5=ia5-80;
        }
      }
      if (tecla == 'd') {
        p++;
        if (p > 161&& p < 240) {
          p--;
        }
        if (p > 1761&& p < 1838) {
          p--;
        }
        if (p > 1600&& p < 1654) {
          p--;
        }
        if (p > 1654&& p < 1680) {
          p--;
        }
        if (p > 1441&& p < 1520) {
          p--;
        }
        if (p > 1280&& p < 1358) {
          p--;
        }
        if (p > 1122&& p < 1200) {
          p--;
        }
        if (p > 962&& p < 1040) {
          p--;
        }
        if (p > 800&& p < 878) {
          p--;
        }
        if (p > 642&& p < 720) {
          p--;
        }
        if (p > 480&& p < 558) {
          p--;
        }
        if (p > 322&& p < 400) {
          p--;
        }
        ia1=ia1+80;
        if (ia1 >= 1920) {
          ia1=ia1-80;
          ia1=ia1-80;
        }
        ia2=ia2-80;
        if (ia2 <= 80) {
          ia2=ia2+80;
          ia2=ia2+80;
        }
        if (ia3 < 1920) {
          ia3++;
        }
        if (ia4 > 80) {
          ia4--;
        }
        if (ia5 > 80) {
          ia5--;
        }
      }
      if (tecla == 'b') {
        p--;
        if (p > 161&& p < 240) {
          p++;
        }
        if (p > 1761&& p < 1838) {
          p++;
        }
        if (p > 1600&& p < 1654) {
          p++;
        }
        if (p > 1654&& p < 1680) {
          p++;
        }
        if (p > 1441&& p < 1520) {
          p++;
        }
        if (p > 1280&& p < 1358) {
          p++;
        }
        if (p > 1122&& p < 1200) {
          p++;
        }
        if (p > 962&& p < 1040) {
          p++;
        }
        if (p > 800&& p < 878) {
          p++;
        }
        if (p > 642&& p < 720) {
          p++;
        }
        if (p > 480&& p < 558) {
          p++;
        }
        if (p > 322&& p < 400) {
          p++;
        }
        ia1=ia1-80;
        if (ia1 <= 80) {
          ia1=ia1+80;
          ia1=ia1+80;
        }
        ia2=ia2-80;
        if (ia2 <= 80) {
          ia2=ia2+80;
          ia2=ia2+80;
        }
        if (ia3 < 1920) {
          ia3--;
        }
        if (ia4 > 80) {
          ia4--;
        }
        ia5=ia5+80;
        if (ia5 >= 1920) {
          ia5=ia5-80;
          ia5=ia5-80;
        }
      }
      if (p == 159) {
        error("Fin del juego", "Has ganado", "Pulsa A para continuar");
        int argc;
        char **argv;
        main(argc, argv);
      }
      if (fin(p, ia1, ia2, ia3, ia4, ia5) == true) {
        error("GAME OVER", "Pulsa A para continuar", " ");
        int argc;
        char **argv;
        main(argc, argv);
      }
    } while (fin(p, ia1, ia2, ia3, ia4, ia5) == false);
}

bool fin(int p, int ia1, int ia2, int ia3, int ia4, int ia5)
{
     if (p == ia1|| p == ia2|| p == ia3|| p == ia4|| p == ia5) {
       return true;
     }
     else {
       return false;
     }
}
