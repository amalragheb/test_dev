#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define BUFFER_SIZE 1024
#define FLUSH_BUFFER -1

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct var_list
{
    int num;
    char *str;
    struct var_list *next;
} var_t;

/**
 * struct esh_data - contains pseudo-arguments to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@esh_name: the shell filename
 *@buffer: address of pointer to buffer
 *@buffer_type: type ||, &&, ;
 *@arg: a string generated from getline containing arguments
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@line_count: the error count
 *@err_num: the error code for exit
 *@flag: flag count line of input
 *@env: linked list local copy of environ
 *@environ: copy of environ
 *@status: status of the last execute command
 */
typedef struct esh_data
{
    char *esh_name;
    char **buffer;
    int buffer_type;
    char *arg;
    char **argv;
    char *path;
    unsigned int line_count;
    int err_num;
    int flag;
    var_t *env;
    char **environ;
    int status;
} esh_t;

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
    char *type;
    int (*func)(esh_t *);
} builtin_t;

/* toem_shloop.c */
int check_builtin(esh_t *);
void execute_command(esh_t *);

/*delet this no need more*/
/* toem_parser.c */
int is_executable(char *);
char *dup_chars(char *, int, int);
char *find_path(char *, char *);

/* toem_string.c */
int _strlen(char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
int _strcmp(char *, char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strchr(char *, char);

/* toem_tokenizer.c */
/*char **strtow(char *, char *)*/
char **_split_str(char *ss, char *meter);
/*int is_delimiter(char, char *)*/
int is_delimiter(char ch, char *dlm);

/* toem_realloc.c */
void free_strings(char **);

/* toem_memory.c */
int pfree(void **);

/* toem_atoi.c */

/* toem_errors1.c */
int _atoi(char *);
void print_error(esh_t *, char *);
int print_d(int);
char *convert_number(long int, int);
void remove_comments(char *);

/* toem_builtin.c */
int esh_exit(esh_t *);
int esh_cd(esh_t *);

/*toem_getline.c */
ssize_t read_line(esh_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void init_esh(esh_t *, char **);
void reset_esh(esh_t *);
void prompt();

/* toem_environ.c */
char *_getenv(esh_t *, const char *);
int esh_env(esh_t *);

/* toem_getenv.c */
char **get_environ(esh_t *);

/* toem_lists.c */
var_t *add_node_end(var_t **, const char *, int);
void free_list(var_t **);

/* toem_lists1.c */
size_t list_len(const var_t *);
char **list_to_strings(var_t *);
var_t *node_starts_with(var_t *, char *, char);

/* toem_vars.c */
int is_chain(esh_t *, char *, size_t *);
void check_chain(esh_t *, char *, size_t *, size_t, size_t);
int replace_vars(esh_t *);
int replace_string(char **, char *);

#endif
