#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void prompt(){
  printf("what's good: ");
}

void check_status(int n){
  if (n == 65280)
    printf("\t!invalid command.\n");
}
