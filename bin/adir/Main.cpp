/* AMAYA OS 2014 */
/* GNU GPL 2014 Daniel Martin */
#include <API/ProcessCtl.h>
#include <Macros.h>
#include <Config.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <TerminalCodes.h>
#include <dirent.h>

int main(int argc,char **argv)
{
    char *dir;
    printf("#########################################################################\r\n");
    printf("# ADIR v0.02 - Amaya OS DIRectory Manager                               #\r\n");
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
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#                                                                       #\r\n");
    printf("#########################################################################\r\n");
    printf("Escribe un directorio a ser leido :");
    gets(dir);
    const char *av[] = { "/bin/echo/echo", "", ZERO };
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    forkexec("/bin/echo/echo", av);
    printf("#########################################################################\r\n");
    printf("# ADIR v0.02 - Amaya OS DIRectory Manager                               #\r\n");
    printf("#########################################################################\r\n");
    printf("#                                                                       #\r\n");
    printf("# Mostrando : ");
    printf(dir, "\r\n");
    const char *dir2[] = { "/bin/ls/ls", dir, ZERO };
    const char *dir3[] = { "/bin/echo/echo", "", ZERO };
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/ls/ls", dir2);
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/echo/echo", dir3);
    forkexec("/bin/echo/echo", dir3);
    printf("########################################################################\r\n");
    printf("# ADIR v0.02 - AMAYA OS DIRectory Manager                              #\r\n");
    printf("########################################################################\r\n");
    printf("# OK                                                                   #\r\n");
    printf("# Finalizando....                                                      #\r\n");
    printf("########################################################################\r\n");
    /* Exit immediately. */
    return EXIT_SUCCESS;
}
