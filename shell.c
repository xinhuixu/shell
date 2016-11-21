#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
  char buf[50];
  printf("what's good:\n");
  
  fgets(buf, sizeof(buf), stdin);
  
  char * bufadd = buf;
  
  printf("value of buf: %s\n",buf);
  printf("address of buf: %u\n",&buf);
  printf("value of bufadd: %u\n",bufadd);
  printf("address of bufadd: %u\n",&bufadd);
  
  printf("\tstrippin newline\n");
  bufadd = strsep(&bufadd, "\n");
  
  printf("value of buf: %s\n",buf);
  printf("value of bufadd: %u\n",bufadd);
  
  char *command[10];

  int i = 0;
  while (bufadd) {
    command[i] = strsep(&bufadd, " ");
    i++;
  }

  command[i] = 0;
  
  
  printf("\texecute\n");
  execvp( command[0], command );

  return 0;
}
