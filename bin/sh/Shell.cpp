/*
 * Copyright (C) 2009 Niek Linnenbank, 2012 Felipe Cabrera, 2016-2017 Daniel Martín
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

#include <TerminalCodes.h>
#include "Shell.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "CommandLineCompletion.h"

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

int Shell::run()
{
    char *cmdStr;
    char host[128], cwd[128] = "/home/";
    
    /* Retrieve current hostname. */
    gethostname(host, sizeof(host));
    
    strncat(cwd,host,strlen(host));
    chdir(cwd);
    
    usrdir = cwd;
    
    /* Ejecutamos la rutina de inicio
     * execute("sh init");
     * printf("\r\n");
     */
    int fd = open("/dev/sh_history", O_WRONLY);
    write(fd, read_file("/dev/sh_history"), get_size("/dev/sh_history"));
    /* Lee los comandos. */    
    while(true) {
        /* Imprime el prompt. */
        prompt();

        /* Espera un comando. */
        cmdStr = getCommand();

        /* Enough input? */
        if (strlen(cmdStr) == 0)
            continue;

	/* Guarda el comando (/dev/sh_history) */
	write(fd, cmdStr, strlen(cmdStr));
	write(fd, "\n", 1);
	/* Ejecuta el comando. */
	execute(cmdStr);
    }
    close(fd);
    return EXIT_SUCCESS;
}

int Shell::execute(char *command)
{
    char *argv[MAX_ARGV];
    char tmp[128];
    ShellCommand *cmd;
    Size argc;
    int pid, status;

    /* Argumento valido? */
    if (!strlen(command))
        return EXIT_SUCCESS;
    
    /* Comenzamos a extraer los argumentos. */
    argc = parse(command, argv, MAX_ARGV);

    /* Do we have a matching ShellCommand? */
    if (!(cmd = ShellCommand::byName(argv[0]))) {
        /* If not, try to execute it as a file directly. */
        if ((pid = forkexec(argv[0], (const char **) argv)) >= 0) {
            waitpid(pid, &status, 0);
            return status;
        }
        /* Try to find it on the livecd filesystem. (temporary hardcoded PATH) */
        else if ((snprintf(tmp, sizeof(tmp), "/bin/%s/%s", argv[0], argv[0]) &&
                ((pid = forkexec(tmp, (const char **) argv)) >= 0)) ||
                (snprintf(tmp, sizeof(tmp), "/sbin/%s/%s", argv[0], argv[0]) &&
                ((pid = forkexec(tmp, (const char **) argv)) >= 0)) ||
                (snprintf(tmp, sizeof(tmp), "/usr/bin/%s/%s", argv[0], argv[0]) &&
                ((pid = forkexec(tmp, (const char **) argv)) >= 0)) ||
                (snprintf(tmp, sizeof(tmp), "/usr/games/%s/%s", argv[0], argv[0]) &&
                ((pid = forkexec(tmp, (const char **) argv)) >= 0)))
        {
            waitpid(pid, &status, 0);
            return status;
        }
        else
            printf("%s: %s\r\n", argv[0],strerror(errno));
    }
    /* Argumentos suficientes? */
    else if (argc - 1 < cmd->getMinimumParams())
        printf("%s: no se han especificado los argumentos (%u minimo)\r\n",
                cmd->getName(), cmd->getMinimumParams());
    /* Lo ejecutamos. */
    else
        return cmd->execute(argc - 1, argv + 1);
    /* Not successful. */
    return EXIT_FAILURE;
}

char * Shell::getCommand()
{
    static char line[1024];
    Size total = 0;

    /* Read a line. */
    while (total < sizeof(line))
    {
        /* Read a character. */
	read(0, line + total, 1);
	
	/* Process character. */
	switch (line[total])
	{
	    case '\r':
	    case '\n':
	    	printf("\r\n");
		line[total] = ZERO;
		return line;

	    case '\b':
		if (total > 0)
		{
		    total--;
		    printf("\b \b");
		}
		break;

	    case '\t':
		line[total] = ZERO;
		total = tab_completion(line, sizeof(line), total);
		break;
	    
	    default:
		printf("%c", line[total]);
		total++;
		break;
	}
    }
    line[total] = ZERO;
    return line;
}

void prompt()
{
    char host[128], cwd[128];
    
    /* Retrieve current hostname. */
    gethostname(host, sizeof(host));
    
    /* Retrieve current working directory. */
    getcwd(cwd, sizeof(cwd));
    
    printf(WHITE GREEN "%s@amaya:" BLUE "%s" WHITE "$ ",
           host, cwd);
}

Size Shell::parse(char *cmdline, char **argv, Size maxArgv)
{
    Size argc;
    
    for (argc = 0; argc < maxArgv && *cmdline; argc++) {
        while (*cmdline && *cmdline == ' ')
            cmdline++;

        argv[argc] = cmdline;

        while (*cmdline && *cmdline != ' ')
            cmdline++;

        if (*cmdline) *cmdline++ = ZERO;
    }
    
    argv[argc] = ZERO;
    return argc;
}
