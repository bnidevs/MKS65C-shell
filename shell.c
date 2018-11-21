#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// pulled from parseargs repo

void exec(char * line){
	char ** array = calloc(5, sizeof(char*));
	char s[100];
	sprintf(s, "%s", line);
	char *s1 = s;
	int x = 0;
	while (s1){
		array[x] = strsep( &s1, " ");
		printf("%s", array[x]);
		x++;
	}

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

int main(){
	prompt();
	return 0;
}