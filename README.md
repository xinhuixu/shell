# shell - xinhui xu pd10

**note**
- assumed white spaces around '>', '|', '<'
- assumed NO white spaces around ';'
  	  e.g. $ ls -l;ls
 
**functionality**
- ^C exits
- input 'exit' exits
- cd (prints message if success!)
- single redirection
- single pipe

**attempted but not achieved**
- cd with empty space => cd ~ (bash behavior)
- separating by ; with spaces around
- handle first cmd token is an operation chr 

**headers**  
- func.c
```
//basic prompt message
void prompt();

//print array of string
void parray(char *[]);

//print string
void pstr(char *);

//exit :)
void bye();

//check if char is special chr: '>','<','|'
int is_op(char *);

//build c1 from the part of c before special chr @ c[i]
void cmd_before(char **c1, char **c, int i);

//build c2 from the part of c after special chr @ c[i]
void cmd_after(char **c2, char **c, int i);

//check for cd and special chr and operates accordingly
int def_check(char *[]);
```
- shell.c (main)
```
//handles ^C exit without error
static void sighandler(int signal);

//takes from stdin and handles sep by ';'
//also handles input exit
int main();
```
