#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

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
  exit(0);
}

void cmd_before(char *c1[], char *c[], int i){
  // set c1 into the c before special chrs
      int j = 0;
      while (j < i) {
        c1[j]=(char *)malloc(sizeof(c[j]));
        strcpy(c1[j],c[j]);
        j++;
      }

      /*
      int fd = open(c[2],O_CREAT|O_RDWR,0644);
      int r = dup2(fd,1);
      close(fd);
      if (r<0){
        perror("dup2");
        return r;
      }*/
}

int def_check(char *c[]){
  //parray(c);
  int err;
  int i;
  
  if (strcmp(c[0],"cd") == 0) { //cd
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

  i = 1;
  while (c[i]) {
  
    if (strcmp(c[i],">") == 0){ //>
      char *c1[i];
      cmd_before(c1,c,i);
      //parray(c1);
      return 0;
    }
    //if (strcmp(c[i],def_str[2]) == 0) //<
    //  redir_i(c,i);
    i++;
  }
  
    //printf("\treach end of def_check\n");
    return execvp(c[0],c);
}
