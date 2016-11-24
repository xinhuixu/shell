#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "func.h"

int main() {

  
  while (1){

    /*
      TODO: 
      - prompt current working dir
      - ? C^D reprints last stdout
      - use file to test instead of retyping
      - sep use ;
      - illegal command should get error
     */

    char buf[50];
    prompt();
    fgets(buf, sizeof(buf), stdin);
    char * bufadd = buf;
    bufadd = strsep(&bufadd, "\n");
    char *command[10];
    int i = 0;
    while (bufadd) {
      command[i] = strsep(&bufadd, " ");
      i++;
    }
    command[i] = 0;
    int f = fork();
    if (f == 0) {
      int err = execvp( command[0], command );
      if (err) {
	exit(err);
      }
    }
    else {
      int status, r;
      r = wait( &status ); // terminated child
      check_status(status);
      printf("\t!wait returned: %d, status: %d\n", r, status);
    }
  }
}
