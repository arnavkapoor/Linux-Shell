
#define ARG_MAX 2048

char myroot[ARG_MAX];
char delimit[6];

char* process[ARG_MAX*20+1];
int run_or_stop[ARG_MAX*20+1];
void sigintHandler(int sig_num);
void sigstopHandler(int sig_num); 


void prompt();
void individual_command(char *inp);
void run_pwd   (char *argv[ARG_MAX],int argc);
void run_echo  (char *argv[ARG_MAX],int argc);
void run_cd	   (char *argv[ARG_MAX] , int argc);
void run_ls	   (char *argv[ARG_MAX] , int argc);
void run_pinfo (char *argv[ARG_MAX] , int argc);
void run_remindme(char *argv[ARG_MAX] , int argc);
void run_setenv  (char *argv[ARG_MAX] , int argc);
void run_unsetenv(char *argv[ARG_MAX] , int argc);
void run_clock 	 (char *argv[ARG_MAX] , int argc);
void run_jobs	 (char *argv[ARG_MAX] , int argc);
void run_killjob (char *argv[ARG_MAX] , int argc);
void run_overkill(char *argv[ARG_MAX] , int argc);
void run_bg		 (char *argv[ARG_MAX] , int argc);
void run_fg		 (char *argv[ARG_MAX] , int argc);




