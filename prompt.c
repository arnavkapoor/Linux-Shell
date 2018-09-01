#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include "headerfile.h"

void get_relative_path(char *cwd , char *ans)
{
	int l1 = strlen(myroot);
	int l2 = strlen(cwd);
	int flag1 = 0;

	if( l2 < l1 )
	{
		for (int i = 0; i < l2; ++i)
			ans[i] = cwd[i];
		return;
	}

	if( l1 <= l2)
		{
			for (int i = 0; i < l1; ++i)
			{
				if(cwd[i] != myroot[i])
					flag1 = 1;
			}
			
			if(flag1 == 0 && l1 == l2)
			{
				ans[0] = '~';
				ans[1] = '\0';
			}
			
			else if (flag1 == 1 && l1 == l2)
			{
				for (int i = 0; i < l1; ++i)
					ans[i] = cwd[i];
			}

			if(l1 == l2)
				return;
		}

	if(flag1 == 1)
	{
		for (int i = 0; i < l2; ++i)
			ans[i] = cwd[i];
		return;
	}
	ans[0] = '~';
	
	for (int i = l1; i < l2; ++i)
		ans[i-l1+1] = cwd[i];
	
	ans[l2-l1+1]='\0';
	return;  
}

void prompt() 
{
    char hostname[ARG_MAX];
    gethostname(hostname,ARG_MAX - 1);
    
    char *user;
    user = getenv("USER");

    char cwd[ARG_MAX];
    getcwd (cwd,ARG_MAX - 1);
   
    char *relpth = malloc(sizeof(char*) * ARG_MAX);
    get_relative_path(cwd,relpth);
    
    printf ("<%s@%s:%s> ",user,hostname,relpth);
}

