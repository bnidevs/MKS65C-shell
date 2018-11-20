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
	}
	free(array);
}

int main(){
	return 0;
}