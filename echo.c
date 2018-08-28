#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include "headerfile.h"

void run_echo(char *argv[ARG_MAX] , int argc)
{
	for (int i = 1; i < argc; ++i)
		printf("%s ",argv[i]);
	printf("\n");
}