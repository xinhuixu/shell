#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {

  while (1){
    char buf[50];
    printf("what's good:\n");
  
    fgets(buf, sizeof(buf), stdin);
  
    char * bufadd = buf;
  
    bufadd = strsep(&bufadd, "\n");
  
    char *command[10];

    int i = 0;
    while (bufadd) {
      command[i] = strsep(&bufadd, " ");
      printf("command[%d]: %s\n",i,command[i]);
      i++;
    }

    command[i] = 0;
  
    printf("\texecute\n");
    int f = fork();
    if (f == 0) {
      printf("\ti'm a child\n");
      execvp( command[0], command );
    }
    else {
      int status, r;
      r = wait( &status );
      printf("\twait returned: %d, status: %d\n", r, status);
    }

    return 0;
  }
}
