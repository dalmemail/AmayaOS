/* AMAYA OS 2014 */
/* This is a part of a AMAYA OS MINI-DESKTOP */
/* CopyRight GNU GPL 2014 Daniel Martin */
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    char *dir;
    printf("#########################################################################\r\n");
    printf("# AXPS v0.01 - Amaya OS PS on X mode                                   #\r\n");
    printf("#########################################################################\r\n");
    printf("#                                                                       #\r\n");
    printf("# It's free software | Usted puede colaborar en este proyecto.          #\r\n");
    printf("# amayaos.wordpress.com | amayaos.dnsd.info                             #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    const char *av[] = { "", "", ZERO };
    forkexec("/bin/ps/ps", av);
    printf("Pulsa ENTER para continuar... ");
    gets(dir);
    const char *a2[] = { "/bin/echo/echo", "", ZERO };
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
    forkexec("/bin/echo/echo", a2);
}
