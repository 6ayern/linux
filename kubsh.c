#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void debug(char line[100]){
printf("%s\n", line);
}

int main(){
char input[100];
while(1){
	fgets(input, 100, stdin);
	input[strlen(input) - 1] = '\0';
	if(strcmp(input, "\\q") == 0) {
		break;
	}
	else if(strncmp(input, "debug ", 5)==0) {
	debug(input);
	} else{
 	printf("%s: command not found\n", input);
	}
 return 0;
}
}
