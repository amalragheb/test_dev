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

/* for command chaining */
#define CMD_OR 1
#define CMD_AND 2

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
    struct liststr *next;
} var_t;

/**
 * struct hsh_data - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 */
typedef struct hsh_data
{
    char *arg;
    char **argv;
    char *path;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    var_t *env;
    char **environ;
    int status;

    char **cmd_buf;   /* pointer to cmd ; chain buffer, for memory mangement */
    int cmd_buf_type; /* CMD_type ||, &&, ; */
} hsh_t;

#define INFO_INIT                                               \
    {                                                           \
        NULL, NULL, NULL, 0, 0, 0, NULL, NULL, NULL, 0, NULL, 0 \
    }

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
    char *type;
    int (*func)(hsh_t *);
} builtin_t;

/* toem_shloop.c */
int find_builtin(hsh_t *);
void execute_command(hsh_t *);

/*delet this no need more*/
/* toem_parser.c */
int is_cmd(hsh_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(hsh_t *, char *, char *);

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
char *_memset(char *, char, unsigned int);
void ffree(char **);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */

/* toem_errors1.c */
int _atoi(char *);
void print_error(hsh_t *, char *);
int print_d(int);
char *convert_number(long int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(hsh_t *);
int _mycd(hsh_t *);

/*toem_getline.c */
ssize_t get_input(hsh_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void set_info(hsh_t *, char **);
void free_info(hsh_t *, int);

/* toem_environ.c */
char *_getenv(hsh_t *, const char *);
int _myenv(hsh_t *);

/* toem_getenv.c */
char **get_environ(hsh_t *);

/* toem_lists.c */
var_t *add_node_end(var_t **, const char *, int);
void free_list(var_t **);

/* toem_lists1.c */
size_t list_len(const var_t *);
char **list_to_strings(var_t *);
var_t *node_starts_with(var_t *, char *, char);

/* toem_vars.c */
int is_chain(hsh_t *, char *, size_t *);
void check_chain(hsh_t *, char *, size_t *, size_t, size_t);
int replace_vars(hsh_t *);
int replace_string(char **, char *);

#endif
