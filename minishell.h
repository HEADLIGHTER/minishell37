#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

//# define PRINT_ERROR_FD 2
//# define DOUBLE_QUOTE 34 //""
//# define SINGLE_QUOTE 39 //'
//# define PIPE 124 //|
//# define DOLLAR 36 //$
# define REDIRECT		3
# define PIPE           4
# define SYNTAX_ERROR "bash: syntax error near unexpected token"
# define SYNTAX_UNEXP_NL "bash: syntax error near unexpected token `newline'"

# define INIT 1
# define PULL 2

typedef struct      s_cmd
{
	char 			**argv;
	char 			*name_file;
	t_list          *token;
	t_list          *file_in;
	t_list          *file_out;
	int             std_in;
	int             std_out;
	int             fd_copy_in;
	int             fd_copy_out;
	int             p_in[2];
	int             p_out[2];
	int             append;
	struct s_cmd    *next;
}                   t_cmd;

typedef struct      s_env
{
	char            *key;
	char            *value;
	int             set;
	struct s_env    *next;
}                   t_env;

typedef struct      s_cnt
{
	unsigned int    s;
	char            *save;
}                   t_cnt;

typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmd;
	char	*line;
	int		last_exit;

}				t_shell;

//cmd.c
t_cmd *cmd_new(void);
t_cmd *cmd_last(t_cmd **cmd);
void tkn_back(t_cmd **begin, char *cntnt);
void cmd_back(t_cmd **cmd, char *id);
//evn.c
t_env *get_env(t_env *env, char *key);
t_env *env_new(char *key, char *vaulue, int set);
void envp_back(t_env **old, t_env *new);
t_env 	*parser_env(char **envp);
//signal.c
t_shell *get_shell(int flag);
t_cnt       *init_cnt(void);
//parsing.c
void split_cmd(char *line, t_cmd **cmd);
t_cmd *parsing(char *line, t_env *envp, int *last_exit);
//utils.c
size_t  escaped(char *str, size_t i, char *sep);
// dollar.c
void replacce(char **s, int i, char *l_e);
static void env_search(char **s, int i, t_env *env);
void env_logic(t_list *tkn, t_env *env, int i, int last_exit);
void	parser_dollar(t_cmd *cmd, t_env *env, int last_exit);
// parsing_special_char
void    parser_redirect(t_cmd *cmd, t_list *token, int ret);
void    parse_pipe(t_cmd *cmd, t_list *tkn, int i);
void parser_special_char(t_cmd *cmd, char *s_char,
						 void (*found)(t_cmd *, t_list *, int));
//clean.c
void    cpy_no_quotes(char *s1, char *s2);
void rm_quote(t_cmd *cmd);
void rm_redirect_pipe(t_cmd *cmd);

#endif
