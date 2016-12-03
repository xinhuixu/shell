#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "func.h"
  
static void sighandler(int signal){
  if (signal == SIGINT) {
    exit(0);
  }
}

int main() {

  while (1){

    signal(SIGINT, sighandler);

    char buf[50];
    prompt();
    fgets(buf, sizeof(buf), stdin);
    char * bufadd = buf;
    *(strchr(bufadd, '\n')) = 0;
    char *command[10];
    int i = 0;
    while ((command[i] = strsep(&bufadd,";"))){
      i++;
    }

    i = 0;
    while (command[i]){

      char *temp = (char *)malloc(sizeof(command[i]));
      strcpy(temp,command[i]);
      char *sc[10];
      int j = 0;
      while ((sc[j] = strsep(&temp," "))) {
	j++;
      }
      
      int f = fork();
      if (f == 0) {
	int err = def_check(sc);
	if (err) {
	  perror("shell");
	  exit(err);
	}
      }
      else {
	int status, r;
	r = wait( &status ); // terminated child
      }
      
      i++;
    }
  }
}
