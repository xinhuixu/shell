#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void prompt(){
  printf("what's good$ ");
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
}

void cmd_after(char *c2[], char *c[], int i){
  int j = 0;
  i++;
  while(c[i]){
    c2[j]=(char *)malloc(sizeof(c[i]));
    strcpy(c2[j],c[i]);
    j++;
    i++;
  }

}

int is_op(char *c){
  return (strcmp(c,">") == 0 ||
	  strcmp(c,"<") == 0 ||
	  strcmp(c,"|") == 0);
}

int def_check(char *c[]){
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
  
    if (is_op(c[i])){
      char **c1 = (char **)malloc(100);
      cmd_before(c1,c,i); //build c1 as cmd before
      char **c2 = (char **)malloc(100);
      cmd_after(c2,c,i);
      int fd, r;
      if (strcmp(c[i],">")==0) {
	fd = open(c2[0],O_CREAT|O_RDWR,0644);
	r = dup2(fd,1);
	execvp(c1[0],c1);
	close(fd);
      }
      else if (strcmp(c[i],"<")==0) {
	fd = open(c2[0],O_CREAT|O_RDWR,0644);
	r = dup2(fd,0); 
	execvp(c1[0],c1);
	close(fd);
      }
      
      free(c1);
      free(c2);
      return 0;
    }

    i++;
  }
  
  //printf("\treach end of def_check\n");
  return execvp(c[0],c);
}
