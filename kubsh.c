#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<signal.h>
#define HISTORY_FILE ".kubsh_history"
sig_atomic_t signal_received = 0;

void debug(char *line){
	printf("%s\n", line);
}

void sig_handler(int signum) {
 signal_received = signum;
 printf("Configuration reloaded");
}

void disk_info(char *device){
 printf("Disk information for %s:\n", device);
 char command[256];
 snprintf(command, sizeof(command), "sudo fdisk -l %s 2>/dev/null", device);
 int result = system(command);
 if(result!=0) {
  printf("Error: Cannot get disk information for %s\n", device);
  printf("Try run ning with sudo or check device name\n");
 }
} 
int main(){
 rl_clear_signals;
 signal(SIGINT, sig_handler);
 read_history(HISTORY_FILE);
 char *input;
 while(true){
  input = readline("$ ");

  if(signal_received) {
   signal_received = 0;
   continue;
   }
   if(input == NULL){
    break;
   }
   add_history(input);
   if(!strcmp(input, "\\q")) {
    break;
   }
   else if(strncmp(input, "debug ", 5)==0) {
    debug(input);
    } else if(!strncmp(input, "\\l /dev/sda", 12)){
     disk_info("/dev/sda");
    } else {
     printf("%s: command not found\n", input);
     }
   free(input);
   }
 write_history(HISTORY_FILE);
 return 0;
}

