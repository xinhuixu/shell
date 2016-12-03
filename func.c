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
  printf("%s\n",c);
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

/*void kill_front_space(char *c){
  int i = 0;
  if (strcmp(c[i]," ") == 0){
    while (c[i]){
      strcpy(c[i],c[i+1]);
      i++;
    }
    //    c[i] = 0;
  }
  }*/

int def_check(char *c[]){
  int err;
  int i;
  int status;
  
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
      cmd_before(c1,c,i);
      char **c2 = (char **)malloc(100);
      cmd_after(c2,c,i);
      int fd, r, stdin, f;
      int fd_p[2]; //pipe
      
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
      else if (strcmp(c[i],"|")==0) {
	stdin = dup(0);
	pipe(fd_p);

	f = fork();
	if (f == 0) {
	  close(fd_p[0]);
	  dup2(fd_p[1],1);
	  err = execvp(c1[0],c1);
	  exit(0);
	} else {
	  wait(&status);
	  close(fd_p[1]);
	  dup2(fd_p[0], 0);
	  err = execvp(c2[0],c2);
	  dup2(stdin, 0);
	}
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
