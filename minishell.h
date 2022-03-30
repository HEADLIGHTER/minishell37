#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <sys/errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
# include <limits.h>
# include <stddef.h>

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
void env_value(t_env *env, char *new_value);
//signal.c
t_shell *get_shell(int flag);
t_cnt       *init_cnt(void);
//parsing.c
void split_cmd(char *line, t_cmd **cmd);
t_cmd *parsing(char *line, t_env *envp, int *last_exit);
//utils.c
size_t  escaped(char *str, size_t i, char *sep);
int     is_builtin(char *token);
void	handel_built_in(t_shell *sh, t_cmd *cmd, t_list *tkn);
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
//cd.c
static char *replace(t_env *env, char *path, int flag);
static int cd_path(t_env *env, char *path, int flag);
int built_in_cd(t_env *env, t_list *tkn);
//echo.c
int built_in_echo(t_list *tkn);
//env.c
int built_in_env(t_env *env);
//pwd.c
int built_in_pwd(void);
// main.c
int         is_var_declaration(char *str);
// export.c
int built_in_export(t_env *env, t_list *tkn);

//envworks
static char	**create_envp(t_env *env);
int			env_size(t_env *env);
void		set_env_value(t_env *env, char *new_value);
char		*get_bin(t_env *env, char *name);

//erroren
void		error_input(void);
void		sig_quit(int sig);

//executor
static void	parent_code(t_shell *sh, t_cmd *cmd, pid_t pid);
void		executor(t_cmd *cmd, t_shell *sh);
void		execve_fct(t_shell *sh, t_cmd *cmd, char *path);

//list
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
int			ft_lstsize(t_list *lst);

//pipes
void		set_read_write_pipe(t_cmd *cmd);
void		set_builtin_pipe(t_cmd *cmd);
void		set_cmd_pipe(t_cmd *cmd);

//fdes
static int	open_file(t_cmd *cmd, t_list *file, int std_fd);
void		set_redirect_fd(t_cmd *cmd, int std_fd);
void		open_fd(t_cmd *cmd);
void		reset_fd(t_cmd *cmd);

//free
int			free_all(t_shell *sh);
void		free_env(t_env *env);
void		free_cmd(t_cmd *cmd);
int			free_split(char **split);

//sig
void		sig_cmd(int sig);
void		sig_child(int sig);
void		sig_main(int sig);
void		sig_quit(int sig);

//utils37
void		no_path(t_cmd *cmd, t_shell *sh);
int			getenv_check(t_env *env, t_list *tkn);
t_list		*f_in_out(t_cmd *cmd, int std_fd);
void		f_copy_in_out(t_cmd *cmd, int std_fd);
int			append(t_list *token, int ret);
void		redir(t_list *token, int ret, t_cmd *cmd);
int			check_input(char *input);

#endif
