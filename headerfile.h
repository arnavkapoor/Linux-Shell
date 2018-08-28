#ifndef HEADER_FILE
#define HEADER_FILE

#define ARG_MAX 2048

char myroot[ARG_MAX];
char delimit[6];

void prompt();
void individual_command(char *inp);
void run_pwd  (char *argv[ARG_MAX],int argc);
void run_echo (char *argv[ARG_MAX],int argc);

#endif