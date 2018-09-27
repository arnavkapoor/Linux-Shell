#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/mman.h>
#include <fcntl.h> 
#include "headerfile.h"

void select_command(char *argv[ARG_MAX], int argc,int bgproc)
{
    if (strcmp(argv[0],"pwd") == 0 || (strcmp(argv[0],"pwd&") == 0)) 
    {
        run_pwd(argv, argc);
        return;
    }
    
    if (strcmp(argv[0],"echo") == 0 || (strcmp(argv[0],"echo&") == 0)) 
    {
        run_echo(argv, argc);
        return;
    }
    
    if (strcmp(argv[0],"cd") == 0 || (strcmp(argv[0],"cd&") == 0))
    {   
        run_cd(argv, argc);
        return;
    }
    
    if (strcmp(argv[0],"ls") == 0 || (strcmp(argv[0],"ls&") == 0))
    {   
        run_ls(argv, argc); 
        return;
    }
    
    if (strcmp(argv[0],"pinfo") == 0 || (strcmp(argv[0],"pinfo&") == 0))
    {   
        run_pinfo(argv, argc); 
        return;
    }
    
    if (strcmp(argv[0],"remindme") == 0 || (strcmp(argv[0],"remindme&") == 0))
    {   
        run_remindme(argv, argc); 
        return;
    }

    if (strcmp(argv[0],"clock") == 0 || (strcmp(argv[0],"clock&") == 0))
    {   
        run_clock(argv, argc); 
        return;
    }
    
    if (strcmp(argv[0],"setenv") == 0 || (strcmp(argv[0],"setenv&") == 0))
    {   
        run_setenv(argv, argc); 
        return;
    }
    
    if (strcmp(argv[0],"unsetenv") == 0 || (strcmp(argv[0],"unsetenv&") == 0))
    {   
        run_unsetenv(argv, argc); 
        return;
    }
    
    if (strcmp(argv[0],"jobs") == 0 || (strcmp(argv[0],"jobs&") == 0))
    {   
        run_jobs(argv, argc); 
        return;
    }
    
    if (strcmp(argv[0],"kjob") == 0 || (strcmp(argv[0],"kjob&") == 0)) 
    {
        run_killjob(argv, argc);
        return;
    }

    if (strcmp(argv[0],"overkill") == 0 || (strcmp(argv[0],"overkill&") == 0)) 
    {
        run_overkill(argv, argc);
        return;
    }
    
    if (strcmp(argv[0],"bg") == 0 || (strcmp(argv[0],"bg&") == 0)) 
    {
        run_bg(argv, argc);
        return;
    }
    if (strcmp(argv[0],"fg") == 0 || (strcmp(argv[0],"fg&") == 0)) 
    {
        run_fg(argv, argc);
        return;
    }

    fork_execute(argv,argc,bgproc);
    return;

}
void execute_pipes(char *argv[ARG_MAX], int argc,int bgproc,int in,int out)
{
    int fd[2];
    int f_in = in;
    int f_out = out;

    char *argv_cp[ARG_MAX];
    int indlen = 0;
    int status;
    
    for (int i = 0; i < argc; ++i)
    {
        if(strcmp(argv[i],"|") == 0)
        {
            argv_cp[indlen] = malloc(sizeof(char)*(ARG_MAX+1));
            argv_cp[indlen] = NULL;
            
            pipe(fd);
            f_out = fd[1];
            int pid = fork();

            if(pid == 0)
            {    
                if(f_in != 0)
                {
                    dup2 (f_in,0);
                    close (f_in);
                }   
                if(f_out != 0)
                {
                    dup2 (f_out,1);
                    close (f_out);
                }
                
                select_command(argv_cp,indlen,bgproc);
                exit(0);
            }

            else if(pid != 0)
                waitpid(-1,&status,WUNTRACED); 

            close(fd[1]);
            f_in = fd[0];

            for (int j = 0; j <= indlen ; ++j)
                free(argv_cp[j]);
            
            indlen = 0;
            continue;
        }

        argv_cp[indlen] = malloc(sizeof(char)*(ARG_MAX+1));
        strcpy(argv_cp[indlen],argv[i]);
        indlen++;
    }
    
    if(f_in != 0)
    {
        dup2 (f_in,0);
        close(f_in);
    }

    if(out != 1)
    {
        dup2(out,1);
        close (out);
    }

    argv_cp[indlen] = malloc(sizeof(char)*(ARG_MAX+1));
    argv_cp[indlen] = NULL;
    
    select_command(argv_cp,indlen,bgproc);
    
    return;

}

void individual_command(char *input) // rename to find_command
{
    
    char* cpinput = input;
    int argc = 0;
    int maxarglength = 0;
    char* token;
    char* argv[ARG_MAX];
    token = strtok_r(cpinput,delimit,&cpinput);
    
    int in = 0;
    int out = 1;

    int ipset = 0;
    int opset = 0;
    int apset = 0;

    int original_ip = dup(0); 
    int original_op = dup(1);

    while (token != NULL) 
    {        
        argv[argc] = malloc(sizeof(char)*(strlen(token)+1));
        strcpy(argv[argc],token);
        argc++;
        if(strcmp(token,"<")==0)
            ipset = argc;
        if(strcmp(token,">")==0)    
            opset = argc;
        if(strcmp(token,">>")==0)    
            apset = argc;

        token = strtok_r(cpinput,delimit,&cpinput); 
    }
    
    if(ipset > 0)
    {
        in = open(argv[ipset],O_RDONLY); 
        if(in < 0)
        {
            perror("bash");
            return;
        }   
        dup2(in,0);
        for (int i = ipset-1; i+2 < argc; ++i)
            argv[i]=argv[i+2];
        argc-=2;
    } 

    if(opset > 0)
    {
        out = open(argv[opset],O_WRONLY | O_CREAT, 0644);
        if(out < 0)
        {
            perror("bash");
            return;
        }   
        dup2(out,1);
        argc-=2;
        argv[opset]='\0';
        argv[opset-1]='\0';
    }         


    if(apset > 0)
    {
        out = open(argv[apset],O_APPEND | O_WRONLY | O_CREAT , 0644);
        if(out < 0)
        {
            perror("bash");
            return;
        }   
        dup2(out,1);
        argc-=2;
        argv[apset]='\0';
        argv[apset-1]='\0';
    }         

    int bgproc = 0;

    if(argv[argc-1][0] == '&')
    {
        bgproc = 1;
        argc--;
    }

    if(argv[argc-1][strlen(argv[argc-1])-1] == '&')
    {
        bgproc = 1;
        argv[argc-1][strlen(argv[argc-1])-1] = '\0';
    }
    argv[argc] = NULL;

    
    execute_pipes(argv,argc,bgproc,in,out);
    for (int i = 0; i <= argc; ++i)
       free(argv[i]);

    if(original_ip != 0)
      dup2(original_ip,0);
    if(original_op != 1)    
       dup2(original_op,1);
   
   return;
}

