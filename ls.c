#include <sys/utsname.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include "headerfile.h"

void run_ls(char *argv[ARG_MAX] , int argc)
{
	char mydir[ARG_MAX];
	getcwd(mydir,ARG_MAX-1);
	
	int hiddenfiles = 0;
	int longlist = 0;
	int singlefile = 0;

	for (int i = 1; i < argc; ++i)
	{
		if(argv[i][0] == '-')
		{
			for (int j = 1; j < strlen(argv[i]); ++j)
			{
				if(argv[i][j] == 'a')
					hiddenfiles = 1;
				if(argv[i][j] == 'l')
					longlist = 1;	
			}
		}
		else if(argv[i][0] == '&')
			continue;
		else if(argv[i][0] == '~')
			sprintf(mydir,"%s%s",myroot,&argv[i][1]);
		else 
			sprintf(mydir,"%s",&argv[i][0]);
	}

	DIR* dir;
	dir = opendir(mydir);
	struct dirent *file;
	int flag = 0;
	
	if(dir == NULL)
	{
		int errnum = errno;
		if(errnum == 2)
		{
			perror("bash");
			return;
		}
		flag = 1;
	}
	
	if (dir != NULL)
		file = readdir(dir);

	
	while(file !=NULL || flag == 1 )
	{
		
		struct stat filestat;
		struct passwd *usr;
		struct passwd *grp;
		
		if(flag == 0)
			lstat(file->d_name,&filestat);   
		
		if(flag == 1)
			lstat(mydir,&filestat);		

		if( flag == 0 && (file->d_name)[0] == '.' && hiddenfiles == 0)
		{
			file = readdir(dir);
			continue;
		}

		if(!longlist && flag == 0)
			printf("  %-18s\n",file->d_name);
		
		if(!longlist && flag == 1)
			printf("  %-18s\n",mydir);
				

		if(longlist)
		{
			usr = getpwuid(filestat.st_uid);
			grp = getpwuid(filestat.st_gid);
			
			if(S_ISDIR(filestat.st_mode))
				printf("d");
			else if (S_ISLNK(filestat.st_mode))
				printf("l");
			else
				printf("-");
			
			printf( (filestat.st_mode & S_IRUSR) ? "r" : "-");
			printf( (filestat.st_mode & S_IWUSR) ? "w" : "-");
			printf( (filestat.st_mode & S_IXUSR) ? "x" : "-");
			printf( (filestat.st_mode & S_IRGRP) ? "r" : "-");
			printf( (filestat.st_mode & S_IWGRP) ? "w" : "-");
			printf( (filestat.st_mode & S_IXGRP) ? "x" : "-");
			printf( (filestat.st_mode & S_IROTH) ? "r" : "-");
			printf( (filestat.st_mode & S_IWOTH) ? "w" : "-");
			printf( (filestat.st_mode & S_IXOTH) ? "x" : "-");
			printf("  %-20ld",filestat.st_size);
			printf("  %-20ld",filestat.st_nlink);
			printf("  %-20s",usr->pw_name);
			printf("  %-20s",grp->pw_name);	
			if(flag == 0)
				printf("  %-20s",file->d_name);
			else if(flag == 1)
				printf("  %-30s",mydir);

			char* mystr = ctime(&filestat.st_mtime);
			printf("%.*s\n",12,mystr+4);
		}
		
		if(flag == 1)
			break; 
		
		file = readdir(dir);
	}

	return;
}
