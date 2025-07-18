#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 100

int main(int argc, char *argv[]){

	char *line = NULL;
	char *cmd = NULL;
	size_t bufsize = 0;
	char *args[MAX_ARGS];

	while(1){
		printf("wish> ");
		getline(&line, &bufsize, stdin);

		if (line==NULL) continue;
		if(line[strlen(line)-1]=='\n'){
			line[strlen(line)-1]='\0';
		}

		while ((cmd=strsep(&line, "&"))!=NULL){

			// separate token by space
			int argc =0;
			char *token = NULL;
			char *ptr = cmd;
			while((token = strsep(&ptr, " \t"))!=NULL){
				if(strlen(token)==0) continue;
				args[argc++] = token;
			}
			args[argc] = NULL;

			if(argc == 0) continue;

			// execute command in child process
			pid_t pid = fork();
			if(pid==0){
				//child process
				char cmd_path[128] = "/bin/";
				strcat(cmd_path, args[0]);

				execv(cmd_path, args);

				// if failed
				fprintf(stderr, "An error has occurred\n");
				exit(1);
			}else{
				// parent process
				wait(NULL);
			}
		}
	}

	free(line);
	return 0;
}
