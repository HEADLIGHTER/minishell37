#include "minishell.h"

int exit_status;
// ------- FREE PART -------

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !(*del))
		return ;
	(*del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *current;
	t_list *trash;

	if (!lst || !*lst || !(*del))
		return ;
	current = *lst;
	while (current)
	{
		trash = current->next;
		ft_lstdelone(current, (*del));
		current = trash;
	}
	*lst = NULL;
}
void    free_cmd(t_cmd *cmd)
{
	t_cmd *tmp;

	while (cmd)
	{
		ft_lstclear(&cmd->token, &free);
		ft_lstclear(&cmd->file_in, &free);
		ft_lstclear(&cmd->file_out, &free);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void    free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		free(env->key);
		free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

int    free_all(t_shell *sh)
{
	free_cmd(sh->cmd);
	free_env(sh->env);
	return (1);
}

void	free_end(t_shell *sh, char *input)
{
	if (input)
		free(input);
	free_all(sh);
}

int	print_free(t_shell *sh)
{
	write(2, "exit\n", 5);
	free_env(sh->env);
	return (1);
}



// ------- FREE PART -------

// ------- EXEC PART -------

// *** freex ***


// *** freex ***
// *** utils ***

int		ft_lstsize(t_list *lst)
{
	int		size;

	size = 0;
	while (lst)
	{
		++size;
		lst = lst->next;
	}
	return (size);
}



static char **create_argv(t_list *tkn)
{
	size_t  i;
	size_t  len;
	char    **argv;

	len = ft_lstsize(tkn);
	if (!(argv = malloc(sizeof(*argv) * (len + 1))))
	{
		write(1, "mini$hell37: malloc: ", 21);
		write(1,  strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
		return (NULL);
	}
	i = 0;
	while (i < len + 1 && tkn)
	{
		if (!(argv[i] = ft_strdup(tkn->content)))
			break ;
		tkn = tkn->next;
		++i;
	}
	argv[i] = NULL;
	return (argv);
}

int len_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
// *** utils ***
void    sig_child(int sig)
{
	static int pid;

	if (pid)
	{
		kill(pid, sig);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quitter (core dumped)\n", 1);
		else if (sig == SIGINT || sig == SIGQUIT)
			ft_putstr_fd("\n", 1);
		pid = 0;
	}
	else
		pid = sig;
}

void    sig_main(int sig)
{
	t_shell *sh;

	(void)sig;
	sh = get_shell(PULL);
	ft_putstr_fd("^C\n", 1);
	signal(SIGINT, sig_main);
	free(sh->line);
	sh->line = NULL;
}

void    sig_quit(int sig)
{
	sig = 0;
	signal(SIGQUIT, sig_quit);
}

// *** pipe ***
void    set_read_write_pipe(t_cmd *cmd)
{
	if (cmd->std_in != PIPE || cmd->std_out != STDOUT_FILENO)
	{
		dup2(cmd->p_out[1], STDOUT_FILENO);
		close(cmd->p_out[0]);
		close(cmd->p_out[1]);
	}
	if (cmd->std_in != STDIN_FILENO || cmd->std_out != PIPE)
	{
		dup2(cmd->p_in[0], STDIN_FILENO);
		close(cmd->p_in[0]);
		close(cmd->p_in[1]);
	}
}

void    set_builtin_pipe(t_cmd *cmd)
{
	if (cmd->std_in == PIPE)
	{
		dup2(cmd->p_in[0], STDIN_FILENO);
		close(cmd->p_in[0]);
		close(cmd->p_in[1]);
	}
	if (cmd->std_out == PIPE)
	{
		dup2(cmd->p_out[1], STDOUT_FILENO);
		cmd->next->p_in[0] = cmd->p_out[0];
		cmd->next->p_in[1] = cmd->p_out[1];
	}
}

void    set_cmd_pipe(t_cmd *cmd)
{
	if (cmd->std_in == PIPE)
	{
		close(cmd->p_in[0]);
		close(cmd->p_in[1]);
	}
	if (cmd->std_out == PIPE)
	{
		cmd->next->p_in[0] = cmd->p_out[0];
		cmd->next->p_in[1] = cmd->p_out[1];
	}
}
// *** pipe ***

// *** fdes ***

static int  open_file(t_cmd *cmd, t_list *file, int std_fd)
{
	int fd;

	fd = -1;
	if (std_fd == STDOUT_FILENO)
	{
		if (cmd->append)
			fd = open(file->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(file->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (std_fd == STDIN_FILENO)
		fd = open(file->content, O_RDONLY);
	return (fd);
}

void        set_redirect_fd(t_cmd *cmd, int std_fd)
{
	int     fd;
	t_list  *file;

	file = (std_fd == STDIN_FILENO) ? cmd->file_in : cmd->file_out;
	(std_fd == STDIN_FILENO) ? (cmd->fd_copy_in = dup(std_fd)) :
	(cmd->fd_copy_out = dup(std_fd));
	while (file)
	{
		if ((fd = open_file(cmd, file, std_fd)) == -1)
		{
			write(2, "mini$hell37: ", 13);
			write(2, (char *)file->content, ft_strlen((char *)file->content));
			write(2, " ", 1);
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
			cmd->std_in = -1;
			return ;
		}
		file = file->next;
		if (file)
			close(fd);
	}
	dup2(fd, std_fd);
	close(fd);
}

void open_fd(t_cmd *cmd) //!!!!!!!!!!!
{
	if (cmd->std_in == PIPE)
		cmd->fd_copy_in = dup(STDIN_FILENO);
	if (cmd->std_out == PIPE)
	{
		pipe(cmd->p_out);
		cmd->fd_copy_out = dup(STDOUT_FILENO);
	}
	if (cmd->std_in == REDIRECT)
		set_redirect_fd(cmd, STDIN_FILENO);
	if (cmd->std_out == REDIRECT)
		set_redirect_fd(cmd, STDOUT_FILENO);
	if (cmd->next && cmd->std_out != PIPE && cmd->next->std_in == PIPE)
	{
		pipe(cmd->p_out);
		cmd->next->p_in[0] = cmd->p_out[0];
		cmd->next->p_in[1] = cmd->p_out[1];
		close(cmd->p_out[1]);
	}
}

void    reset_fd(t_cmd *cmd)
{
	if (cmd->std_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_copy_out, STDOUT_FILENO);
		close(cmd->fd_copy_out);
	}
	if (cmd->std_in != STDIN_FILENO)
	{
		dup2(cmd->fd_copy_in, STDIN_FILENO);
		close(cmd->fd_copy_in);
	}
}

// *** fdes ***
// *** exist ***

int	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (-1);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (1);
}

char    *get_bin(t_env *env, char *name)
{
	int         i;
	char        **split;
	char        *path;
	char        *s;
	struct stat buf;

	if (stat(name, &buf) == 0 && buf.st_mode & S_IXUSR && !S_ISDIR(buf.st_mode))
		return (ft_strdup(name));
	if (!(env = get_env(env, "PATH")))
		return (NULL);
	i = -1;
	path = NULL;
	split = ft_split(env->value, ':');
	while (split && split[++i])
	{
		s = ft_strjoin(split[i], "/");
		path = ft_strjoin(s, name);
		free(s);
		if (!stat(path, &buf) && buf.st_mode & S_IXUSR && !S_ISDIR(buf.st_mode))
			break ;
		free(path);
		path = NULL;
	}
	free_split(split);
	return (path);
}
// *** exist ***
int is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (!ft_strncmp("exit", cmd, 5))
		return (2);
	if (!ft_strncmp("cd", cmd, 3))
		return (1);
	else if (!ft_strncmp("echo", cmd, 5))
		return (1);
	else if (!ft_strncmp("env", cmd, 4))
		return (1);
	else if (!ft_strncmp("pwd", cmd, 4))
		return (1);
	else if (!ft_strncmp("export", cmd, 7))
		return (1);
	else if (!ft_strncmp("unset", cmd, 6))
		return (1);
	return (0);
}

int exec_builtin(t_shell *sh, t_cmd *cmd, t_list *tkn)
{
	set_builtin_pipe(cmd);
	if (!ft_strncmp(tkn->content, "cd", 3))
		printf("Ready to builtin\n");
	else if (!ft_strncmp(tkn->content, "echo", 5))
		printf("Ready to builtin\n");
	else if (!ft_strncmp(tkn->content, "env", 4))
		printf("Ready to builtin\n");
	else if (!ft_strncmp(tkn->content, "exit", 5))
		printf("Ready to builtin\n");
	else if (!ft_strncmp(tkn->content, "export", 7))
		printf("Ready to builtin\n");
	else if (!ft_strncmp(tkn->content, "pwd", 4))
		printf("Ready to builtin\n");
	else if (!ft_strncmp(tkn->content, "unset", 6))
		printf("Ready to builtin\n");
	return (0);
}



int     env_size(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		++i;
		env = env->next;
	}
	return (i);
}

void    env_add_back(t_env **begin, t_env *new)
{
	t_env   *curr;

	if (!begin || !new)
		return ;
	if (!*begin)
	{
		*begin = new;
		new->next = NULL;
		return ;
	}
	curr = *begin;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	new->next = NULL;
}

void    set_env_value(t_env *env, char *new_value)
{
	size_t i;

	i = find_char(new_value, '=');
	free(env->value);
	if (new_value[i] == '=')
		env->value = ft_substr(new_value, i + 1, ft_strlen(new_value + i + 1));
	else
		env->value = ft_strdup(new_value);
}


static void parent_code(t_shell *sh, t_cmd *cmd, pid_t pid)
{
	set_cmd_pipe(cmd);
	sig_child(pid);
	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	waitpid(pid, &sh->last_exit, 0);
	signal(SIGINT, sig_main);
	signal(SIGQUIT, sig_quit);
	sh->last_exit = WEXITSTATUS(sh->last_exit);
}

static void	exec_cmd(t_shell *sh, char *path, char **av, char **ev)
{
	if (execve(path, av, ev) == -1)
	{
		write(1, "mini$hell37: execve: ", 21);
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
		free(path);
		free_split(av);
		free_split(ev);
		free_all(sh);
		exit(1);
	}
}
static char **create_envp(t_env *env)
{
	int     i;
	size_t  len;
	char    **envp;

	if (!(envp = malloc(sizeof(*envp) * (env_size(env) + 1))))
		return (NULL);
	i = 0;
	while (env)
	{
		len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
		if (!(envp[i] = malloc(len)))
		{
			write(1, "mini$hell37: malloc: ", 21);
			write(1,  strerror(errno), ft_strlen(strerror(errno)));
			write(1, "\n", 1);
			break ;
		}
		ft_bzero(envp[i], len);
		ft_strlcat(envp[i], env->key, len);
		ft_strlcat(envp[i], "=", len);
		ft_strlcat(envp[i++], env->value, len);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
void execve_fct(t_shell *sh, t_cmd *cmd, char *path)
{
	pid_t   pid;
	char    **ev;
	char    **av;

	if ((pid = fork()) == -1)
	{
		write(1, "mini$hell37: fork: ", 19);
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
	}
	else if (pid > 0)
		parent_code(sh, cmd, pid);
	else
	{
		set_read_write_pipe(cmd);
		av = create_argv(cmd->token);
		ev = create_envp(sh->env);
		exec_cmd(sh, path, av, ev);
	}
	free(path);
}

int         is_var_declaration(char *str)
{
	size_t i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		++i;
	if (str[i] != '=')
		return (0);
	else
		++i;
	while (ft_isalnum(str[i]) || ft_isinset(str[i], "_-:./;"))
		++i;
	if (str[i])
		return (0);
	return (1);
}

static int  handle_logic(t_list *tkn, t_env *env, t_env **new)
{
	size_t  i;
	t_env   *tmp;

	if (!is_var_declaration(tkn->content))
	{
		free_env(*new);
		return (1);
	}
	else if ((tmp = get_env(env, tkn->content)) ||
			 (tmp = get_env(*new, tkn->content)))
		set_env_value(tmp, tkn->content);
	else
	{
		i = find_char(tkn->content, '=');
		tmp = env_new(ft_substr(tkn->content, 0, i), ft_substr(
				tkn->content, i + 1, ft_strlen(tkn->content + i + 1)), 0);
		env_add_back(new, tmp);
	}
	return (0);
}

void        parse_var_declaration(t_cmd *cmd, t_list **tk, t_env *env)
{
	t_list  *tkn;
	t_env   *new;

	tkn = cmd->token;
	new = NULL;
	while (tkn)
	{
		if (handle_logic(tkn, env, &new))
		{
			*tk = tkn;
			return ;
		}
		tkn = tkn->next;
	}
	ft_lstclear(&cmd->token, &free);
	cmd->token = NULL;
	*tk = NULL;
	env_add_back(&env, new);
}

void	builtin_cd(t_shell *sh, t_list *token)
{
	printf("builtin cd");
}

void executor(t_cmd *cmd, t_shell *sh)
{
	char        *path;
	struct stat buf;

	while (cmd)
	{
		if (cmd->token && is_var_declaration(cmd->token->content))
			parse_var_declaration(cmd, &cmd->token, sh->env);
		open_fd(cmd);
		if (cmd->token && cmd->std_in != -1)
		{
			if (is_builtin(cmd->token->content))
				exec_builtin(sh, cmd, cmd->token);
			else if (!(path = get_bin(sh->env, cmd->token->content)))
			{
				if (stat(cmd->token->content, &buf) == 0 && S_ISDIR(buf.st_mode))
					builtin_cd(sh, cmd->token);
				else
				{
					write(1, "mini$hell37: " , 13);
					write(1, cmd->token->content, ft_strlen(cmd->token->content));
					write(1, ": command not found\n", 20);
					sh->last_exit = 127;
				}
			}
			else
				execve_fct(sh, cmd, path);
		}
		reset_fd(cmd);
		cmd = cmd->next;
	}
	free_cmd(sh->cmd);
}
// ------- EXEC PART -------

// ------- MAIN PART -------

void	error_input(void)
{
	write(2, "mini$hell37: syntax error near unexpected token '|'\n", 52);
}

void	sig_cmd(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		exit (1);
	}
}

int	check_input(char *input)
{
	int i;
	int dif;

	i = 0;
	dif = 0;
	while(input[i])
	{
		if (input[i] != ' ' && input[i] != '|')
			dif = 1;
		if (input[i] == '|')
		{
			if (dif == 0)
				return (1);
			dif = 0;
		}
		i++;
	}
	return (0);
}

void	start_exec(t_shell *sh, char *input)
{
	sh->cmd = NULL;
	sh->line = input;
	sh->cmd = parsing(sh->line, sh->env, &sh->last_exit);
	free(sh->line);
	if (input != NULL && sh->cmd)
		executor(sh->cmd, sh);
}

int	main(int ac, char **av, char **envp)
{
	char *input;
	t_shell *sh;

	sh = get_shell(INIT);
	sh->env = parser_env(envp);
	signal(SIGINT, sig_cmd);
	signal(SIGQUIT, SIG_IGN);
	if (!ac && !av)
		return (0);
	while (1)
	{
		input = readline("mini$hell37> ");
		add_history(input);
		signal(SIGINT, sig_cmd);
		signal(SIGQUIT, SIG_IGN);
		if (input == NULL)
			return (print_free(sh));
		if (check_input(input) != 0)
			error_input();
		else
			start_exec(sh, input);
		free_end(sh, input);
	}
}