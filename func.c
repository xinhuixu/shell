#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *def_str[2] = {
  "cd",
  "exit"
};

void prompt(){
  printf("what's good: ");
}

void parray(char *c[]){
  int i = 0;
  while (c[i]){
        printf("c[%d] = %s\n",i,c[i]);
	i++;
  }
}

void pstr(char *c){
  printf("str = %s\n",c);
}

/*void check_status(int n){
  if (n == 65280)
    printf("\t!invalid command.\n");
    }*/

int def_check(char *c[]){
  parray(c);
  if (strcmp(c[0],def_str[0]) == 0) { //cd
    if (c[1]){
      /*if (strcmp(c[1],"\n") == 0)
	return chdir("~"); //bash behavior */
      int res = chdir(c[1]);
      if (res == 0)
	printf("cd %s: success\n",c[1]);
      return res;
    }
    else {
      return -1;
    }
  }
  else
    return execvp(c[0],c);
}
