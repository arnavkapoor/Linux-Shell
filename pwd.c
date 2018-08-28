#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include "headerfile.h"


void run_pwd(char *argv[ARG_MAX] , int argc)
{
	char pwd[ARG_MAX];
	getcwd(pwd,ARG_MAX-1);
	printf("%s\n",pwd);
}