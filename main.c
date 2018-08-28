#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headerfile.h"

int main () {
   
    getcwd(myroot,ARG_MAX-1);
    strncpy(delimit," \t\r\n\v\f",6);
   
    while(1)
    {   
        prompt();
        char command[ARG_MAX];
        fgets(command,ARG_MAX,stdin);
        char *input = strtok(command, ";");

        while(input!=NULL)
        {
            individual_command(input);
            input = strtok(NULL,";");   
        }

    }    
  
    return 0;
}
