#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

char *def_str[3] = {
  "cd",
  ">",
  "|"
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

void bye(){
  printf("all parties ends\n");
  exit(0);
}

int def_check(char *c[]){
  //parray(c);

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

  else if (c[1] && (strcmp(c[1],def_str[1]) == 0)) { //>
    if (c[2]) {
      int fd = open(c[2],O_CREAT|O_RDWR,0777);
      //int din = dup(1);
      dup2(fd,1);
      //dup2(din,1);
      return 0;
    }
  }
  
  else {
    printf("\treach end of def_check\n");
    return execvp(c[0],c);
  }
}
