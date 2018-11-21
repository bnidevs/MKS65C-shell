#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// pulled from parseargs repo

char ** pargs(char * line, char * dlim){
	char ** array = calloc(16, sizeof(char*));
	char s[1024];
	sprintf(s, "%s", line);
	char *s1 = s;
	int x = 0;
	while (s1){
		array[x] = strsep(&s1, dlim);
		x++;
	}
	return array;
}

void exec(char * line){
	char * dlim = " ";
	char ** array = pargs(line, dlim);

	int f = fork();
	if(!f){
		execvp(array[0], array);
	}else{
		wait(NULL);
	}
	free(array);
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

	char * dlim = ";";
	char ** array = pargs(line, dlim);
	return array;
}

int main(){
	while(1){
		prompt();
		char ** cmds = readr();

		int inc = 0;
		while(cmds[inc]){
			exec(cmds[inc]);
				exit(0);
			}
		}
	}
	return 0;
}