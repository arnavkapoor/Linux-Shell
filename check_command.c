#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include "headerfile.h"


void select_command(char *argv[ARG_MAX], int argc)
{
    if (strcmp(argv[0],"pwd") == 0) 
        run_pwd(argv, argc);
    if (strcmp(argv[0],"echo") == 0) 
        run_echo(argv, argc);
}

void individual_command(char *input) // rename to find_command
{
    char* cpinput = input;
    int argc = 0;
    int maxarglength = 0;
    char* token;
    char* argv[ARG_MAX];

    while (token = strtok_r(cpinput,delimit,&cpinput))
      {
         argv[argc] = malloc(sizeof(char)*(strlen(token)+1));
         strcpy(argv[argc],token);
         argc++;
      }
    
    select_command(argv,argc);

    for (int i = 0; i < argc; ++i)
       free(argv[i]);

}

