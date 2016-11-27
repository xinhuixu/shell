#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "func.h"

int main() {
  
  while (1){

    /*
      TODO: 
      - ? C^D reprints last stdout
      - use file to test instead of retyping
      - sep use ;
     */

    char buf[50];
    prompt();
    fgets(buf, sizeof(buf), stdin);
    char * bufadd = buf;
    *(strchr(bufadd, '\n')) = 0;
    char *command[10];
    int i = 0;

    while ((command[i] = strsep(&bufadd," ")))
	   i++;
	   
    int f = fork();
    if (f == 0) {
      int err = def_check(command);
      
      if (err) {
	perror("shell");
	exit(err);
      }
    }
    else {
      int status, r;
      r = wait( &status ); // terminated child
      //check_status(status); //currently replaced by perror()
      printf("\t!wait returned: %d, status: %d\n", r, status);
    }
  }
}
