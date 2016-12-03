#ifndef FUNC_H
#define FUNC_H

void prompt();
void parray(char *[]);
void pstr(char *);
void bye();
void cmd_before(char **, char **, int);
void cmd_after(char **, char **, int);
int is_op(char *);
int check_status(int);
int def_check(char *[]);

#endif
