#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

char * strip(char * material){
	while(!strncmp(material, " ", 1)){
		material++;
	}

	char * end = strchr(material, 0);
	while(!strncmp((end - 1), " ", 1)){
		end--;
	}
	*end = 0;
	return material;
}

char ** pargs(char * line, char * dlim){
	char ** array = calloc(16, sizeof(char*));
	char *s1 = line;
	int x = 0;
	while (s1){
		array[x] = strip(strsep(&s1, dlim));
		x++;
	}
	return array;
}

void print_arr(char ** args) {
    int i = 0;
    while (args[i]) {
        i++;
    }
}

void exec(char * line){
	if(strchr(line, 62)){
		char ** array = pargs(line, ">");

		int f = fork();
		if(!f){
			int fd = open(array[1], O_CREAT | O_WRONLY, 0777);
			dup2(fd, 1);
			char ** cmdarray = pargs(array[0], " ");
			execvp(cmdarray[0], cmdarray);
			free(cmdarray);
			exit(0);
		}else{
			wait(NULL);
		}

		free(array);
	}else if(strchr(line, 60)){
		char ** array = pargs(line, "<");

		int f = fork();
		if(!f){
			int fd = open(array[1], O_CREAT | O_RDONLY, 0777);
			dup2(fd, 0);
			char ** cmdarray = pargs(array[0], " ");
			execvp(cmdarray[0], cmdarray);
			free(cmdarray);
			exit(0);
		}else{
			wait(NULL);
		}

		free(array);
	}else{
		char ** array = pargs(line, " ");

		if(!strcmp(array[0], "cd")){
			chdir(array[1]);
		}else if(!strcmp(array[0], "exit")){
			exit(0);
		}else{
			int f = fork();
			if(!f){
				execvp(array[0], array);
				exit(0);
			}else{
				wait(NULL);
			}
		}
		free(array);
	}
}

void prompt(){

	//hostname

	char * host = malloc(64);
	gethostname(host, 64);
	char * cut = strchr(host, 46);
	*cut = 0;

	//currdir

	char * ccwd = malloc(128);
	getcwd(ccwd, 128);
	cut = strchr(ccwd, 0);
	while(!strchr(cut - 1, 47)){
		cut--;
	}
	char * cwd = cut;

	//usrname

	char * usr = malloc(16);
	getlogin_r(usr, 16);

	printf("%s:%s %s$ ", host, cwd, usr);
	free(host);
	free(ccwd);
	free(usr);
}

char ** readr(){
	char * line = malloc(1024);
	fgets(line, 1024, stdin);

	char * inc = line;
	while(strcmp(inc, "\n") && *inc){
		inc++;
	}
	*inc = 0;

	char * dlim = ";";
	char ** array = pargs(line, dlim);
	print_arr(array);
	return array;
}

int main(){
	while(1){
		prompt();
		char ** cmds = readr();

		int inc = 0;
		while(cmds[inc]){
			exec(cmds[inc]);
			if(!strcmp(cmds[inc], "exit")){
				exit(0);
			}
			inc++;
		}
	}
}