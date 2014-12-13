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
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <amaya.h>
#include <string.h>
#include <files.h>

void newcalc();

int getnum()
{
    static int ch[1024];
    read(0, ch, 1);
    
    return ch[0];
}

void amayacalc()
{
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
    bg();
    window("AmayaFACT v0.1", 35);
    bar("[N]ueva factura [S]alir");
    do {
      tecla=getchar();
    } while (tecla != 's'&& tecla != 'n');
    switch (tecla) { //El usuario selecciona una opcion....
      case 's':
        int argc;
        char **argv;
        main(argc, argv);
      break;
      case 'n':
        newcalc();
      break;
    }
}

void newcalc()
{
    char *newline="\r\n";
    char inicial[128]="#     A      B     C     D";
    char inicial2[128]="1   ITEM    NO    UNIT   COST";
    int fd;
    char ruta[128]="/dev/";
    char nombre[128];
    printf("Nombre del archivo: ");
    gets_s(nombre, 128);
    if (nombre[0] != '/') {
      strcat(ruta, nombre);
    }
    else {
      strcpy(ruta, nombre);
    }
    touch(ruta, S_IWUSR | S_IRUSR);
    if ((fd = open(ruta, O_WRONLY)) < 0) {
        error("ERROR", "Al abrir el archivo", "Pulsa A");
        int argc;
        char **argv;
        main(argc, argv);
    }
    write(fd, inicial, strlen(inicial));
    write(fd, newline, 2);
    write(fd, inicial2, strlen(inicial2));
    write(fd, newline, 2);
    int n;
    printf("Numero de ITEM(s) : \r\n");
    n=getnum();
    n=n-48;
    n=n-1;
    int resultado[n];
    int i;
    int cuenta;
    char item[n][128];
    char no[128];
    char unit[128];
    int n1;
    int n2;
    int resultadofinal=0;
    int numeros[n];
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
    for (i=0; i < 2000; i++) { //Limpiamos la pantalla....
      vga[i]=VGA_CHAR(' ', BLACK, BLACK);
    }
    window("AmayaFACT - Sin nombre", 30);
    printf("#     A      B     C     D\r\n");
    printf("1   ITEM    NO    UNIT   COST\r\n");
    for (cuenta=0; cuenta <= n; cuenta++) {
      printf("Introduce el nombre del Item ");
      printf("%d", cuenta);
      printf(": ");
      gets_s(item[cuenta], 128);
      printf("Introduce el numero (NO.): ");
      gets_s(no, 128);
      printf("Introduce precio por unidad (UNIT): ");
      gets_s(unit, 128);
      n1=atoi(unit);
      n2=atoi(no);
      resultado[cuenta]=n1 * n2;
      //printf("%d", n1 * n2);
      write(fd, "    ", 4);
      write(fd, item[cuenta], strlen(item[cuenta]));
      int s;
      if (strlen(item[cuenta])==4) {
        s=4;
      }
      if (strlen(item[cuenta])==5) {
        s=3;
      }
      if (strlen(item[cuenta])==6) {
        s=2;
      }
      for (i=0; i < s; i++) {
        write(fd, " ", 1);
      }
      write(fd, no, strlen(no));
      if (strlen(no)==1) {
        s=5;
      }
      if (strlen(no)==2) {
        s=4;
      }
      if (strlen(no)==3) {
        s=3;
      }
      for (i=0; i < s; i++) {
        write(fd, " ", 1);
      }
      write(fd, unit, strlen(unit));
      if (strlen(unit)==1) {
        s=5;
      }
      if (strlen(unit)==2) {
        s=4;
      }
      if (strlen(unit)==3) {
        s=3;
      }
      for (i=0; i <= s; i++) {
        write(fd, " ", 1);
      }
      char res[128];
      itoa(res, 10, resultado[cuenta]);
      write(fd, res, strlen(res));
      write(fd, newline, 2);
      resultadofinal=resultadofinal+resultado[cuenta];
      if (cuenta == n) {
        for (cuenta=0; cuenta <= n; cuenta++) {
          resultadofinal=resultadofinal+resultado[cuenta];
        }
        resultadofinal=resultadofinal/2;
        char line[128]="---------------------------------------------";
        write(fd, line, strlen(line));
        write(fd, newline, 2);
        write(fd, "Total: ", 7);
        char resultadofinalchar[128];
        itoa(resultadofinalchar, 10, resultadofinal);
        write(fd, resultadofinalchar, strlen(resultadofinalchar));
        write(fd, newline, 2);
      }
    }
    //printf("%d", numeros[0]);
    //printf("%d", numeros[1]);
    for (i=0; i < 2000; i++) {
      vga[i]=VGA_CHAR(' ', BLACK, BLACK);
    }
    file *f = new file();
    f->setpath(ruta);
    f->f_open(O_RDONLY);
    char *ch = f->readAll();
    f->f_close();
    
    printf("%s", ch);
    printf("\r\n");
    bar("[A] Aceptar");
    char teclaa;
    do {
      teclaa=getchar();
    } while (teclaa != 'A'&& teclaa != 'a');
    if (teclaa == 'A'|| teclaa == 'a') {
      int argc;
      char **argv;
      main(argc, argv);
    }
}
