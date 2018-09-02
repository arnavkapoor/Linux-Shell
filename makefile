#make file - this is a comment section
 
CC=gcc  #compiler
TARGET=shell #target file name
 
all: 
	$(CC) main.c check_command.c cd.c clock.c echo.c ls.c pinfo.c prompt.c pwd.c remindme.c -o $(TARGET)
 
clean:
	rm *.o $(TARGET)