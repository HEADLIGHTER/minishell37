#include "minishell.h"

int exit_status;
// ------- FREE PART -------

int	free_all(t_shell **sh)
{
	return (1);
}

void free_numfd(int **numfd)
{
	int i;

	i = 0;
	while (numfd[i])
	{
		free(numfd[i]);
		i++;
	}
	free(numfd);
}

void	free_end(t_shell **sh, char *input)
{
	if (input)
		free(input);
	free_all(sh);
}

int	print_free(t_shell **sh)
{
	printf("exit\n");
	//clean_env();
	return (free_all(sh));
}

// ------- FREE PART -------

// ------- EXEC PART -------

// *** freee ***
void	close_fd_all(t_cmd **cmdl)
{
	t_cmd	*cur;

	cur = *cmdl;
	while (cur)
	{
		if (cur->fd_copy_in != 0)
			close(cur->fd_copy_in);
		if (cur->fd_copy_out != 1)
			close(cur->fd_copy_out);
		cur = cur->next;
	}
}

void	free_fd_mall_error(t_commande_line **first)
{
	close_fd_all(first);
	exit (50);
}

void	free_str_fd_env_pid(t_commande_line **cmd, pid_t *pid, char **str)
{
	free_all(cmd);
	//clean_env();
	free(pid);
	free(str);
	exit(1);
}

void	free_str_fd_malloc_error(char **str, t_commande_line **first)
{
	free(str);
	close_fd_all(first);
	exit (50);
}

void	free_file_name(char *file_name)
{
	if (file_name != NULL)
	{
		unlink(file_name);
		free(file_name);
	}
}

void	free_str_fd_all_env_pid(t_commande_line **cmd, pid_t *pid, char **str)
{
	free_all(cmd);
	//ft_clean_env();
	free(pid);
	free(str);
	exit(1);
}
// *** freee ***
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
		printf("mini$hell37: malloc: %s\n", strerror(errno));
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

void	fill_argv(t_cmd *cmd)
{

	while (cmd)
	{
		cmd->argv = create_argv(cmd->token);
		cmd = cmd->next;
	}
}

t_env	**get_address_env(void)
{
	static t_env	*new = NULL;

	return (&new);
}
// *** utils ***
void sig_cmd2(int sig)
{
	exit_status = sig;
	if (sig == 2)
	{
		exit_status = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
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

// *** pipe ***
int init_pipe(int i, int **numfd, t_cmd *curr)
{
	numfd[i] = malloc(sizeof(int) * (2));
	if (numfd[i] == NULL)
		return (1);
	if (pipe(numfd[i]) == -1)
		return (1);
	if (i == 0)
		curr->fd_copy_in = 0;
	else
		curr->fd_copy_in = numfd[i - 1][0];
	if (curr->next == NULL)
	{
		close(numfd[i][0]);
		close(numfd[i][1]);
		curr->fd_copy_out = 1;
	}
	else
		curr->fd_copy_out = numfd[i][1];
	return (0);
}

int open_pipe(t_cmd *cmd)
{
	t_cmd	*curr;
	int 	**numfd;
	int		i;
	int 	ret;

	i = 0;
	curr =cmd;
	numfd = malloc(sizeof(int *) * (len_cmd(curr) + 1));
	if (numfd == NULL)
		return (1);
	numfd[len_cmd(curr)] == NULL;
	while (curr)
	{
		ret = init_pipe(i, numfd, curr);
		if (ret)
		{
			free_numfd(numfd);
			return (ret);
		}
		curr = curr->next;
		i++;
	}
	free_numfd(numfd);
	return (0);
}
// *** pipe ***

// *** fdes ***
int open_fd(t_cmd *cmd) //!!!!!!!!!!!
{
	t_list 	*curr;

	curr = cmd->token;
}

// *** fdes ***
// *** exist ***
char	*write_bad_cmd_free(char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
	free(str);
	return (NULL);
}
char	*get_acces(char *str, char *path)
{
	char	*back_slash;
	char	*new;

	back_slash = ft_strjoin(path, "/");
	if (back_slash == NULL)
		return (NULL);
	new = ft_strjoin(back_slash, str);
	free(back_slash);
	if (new == NULL)
		return (NULL);
	return (new);
}
int	try_acces(char *str, char *path)
{
	char	*try;

	try = get_acces(str, path);
	if (try == NULL)
		return (2);
	if (access(try, X_OK) == 0)
	{
		free(try);
		return (1);
	}
	free(try);
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
	}
	if (split)
		free(split);
}

char	*free_split_ret_null(char **split_path)
{
	free_split(split_path);
	return (NULL);
}

char	*write_bad_cmd_free_split(char *str, char **split_path)
{
	free_split(split_path);
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
	free(str);
	return (NULL);
}

char	*get_bin_argv0(char *str, char *path, int i)
{
	int		ret;
	char	**split_path;
	char	*try;

	if (str && (str[0] == '.' || str[0] == '/'))
		return (str);
	split_path = ft_split(path, ':');
	if (split_path == NULL)
		return (write_bad_cmd_free(str));
	while (split_path[i] && str[0] != '\0')
	{
		ret = try_acces(str, split_path[i]);
		if (ret == 1)
		{
			try = get_acces(str, split_path[i]);
			free_split(split_path);
			return (try);
		}
		if (ret == 2)
			return (free_split_ret_null(split_path));
		i++;
	}
	write_bad_cmd_free_split(str, split_path);
	exit_status = 127;
	return (str);
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

int exec_bi_fd(char *cmd, char **args, t_cmd *first, pid_t *pid)
{
	if (cmd == NULL)
		return (0);
	if (ft_strncmp("exit", cmd))
	{
		//exit_builtin();
		printf("ready to exit\n");
		return (1);
	}
	/*if (ft_strncmp("cd", cmd))
		builtin_cd(args);
	else if (ft_strncmp("echo", cmd))
		builtin_echo_fd();
	else if (ft_strncmp("env", cmd))
		builtin_env();
	else if (ft_strncmp("pwd", cmd))
		builtin_pwd_fd();
	else if (ft_strncmp("export", cmd))
		builtin_export_fd();
	else if (ft_strncmp("unset", cmd))
		builtin_unset();*/
	if (ft_strncmp("builtin", cmd))
		printf("ready to builtin_fd\n");
	return (0);
}

int no_forking(t_cmd *cmd, pid_t pid_t)
{
	if (cmd->argv == NULL)
		return (0);
	else if (exec_bi_fd(cmd->argv[0], cmd->argv, cmd, pid) != 0)
		return (0);
	return (0);
}

char	**env_to_tab(t_env **envp)
{
	char	**new;
	t_env	*cur;
	int		i;

	i = 0;
	cur = *envp;
	while (cur)
	{
		cur = cur->next;
		i++;
	}
	new = malloc(sizeof(char *) * (i + 1));
	new[i] = NULL;
	cur = *envp;
	i = 0;
	while (cur)
	{
		new[i] = cur->key;
		i++;
		cur = cur->next;
	}
	return (new);
}

char	*ft_get_env(char *str)
{
	t_env	**env_list;

	env_list = get_address_env();
	return (NULL);
}

int execve_fct(t_cmd *curr, t_cmd *first, pid_t *pid)
{
	char **str;

	dup2(curr->fd_copy_in, STDIN_FILENO);
	dup2(curr->fd_copy_out, STDOUT_FILENO);
	close_fd_all(first);
	str = env_to_tab(get_address_env());
	if (str == NULL)
		free_fd_mall_error(first);
		if (is_builtin(curr->argv[0]) == 0)
		{
			if (curr->argv[0] == NULL)
				free_str_fd_env_pid(first, pid, str);
			curr->argv[0] = get_bin_argv0(curr->argv[0], ft_get_env("PATH") ,0);
		}
	if (curr->argv[0] == NULL)
		free_str_fd_malloc_error(str, first);
	free_file_name((*curr)->name_file);
	if ((*curr)->fd_copy_in < 0 || (*curr)->fd_copy_out < 0)
		free_str_fd_all_env_pid(first, pid, str);
	if (is_builtin((*curr)->argv[0]))
		handle_builtin(); //!!
	else
		exec_cmd();
	return (0);
}

int multifork(pid_t *pid, int i, t_cmd *cmd, t_cmd *curr)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid[i] = fork();
	if (pid[i] == -1)
		exit(1);
	if (pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve_fct(curr, cmd, pid);
	}
	if (curr->fd_copy_in != 0)
		close(curr->fd_copy_in);
	if (curr->fd_copy_out != 0)
		close(curr->fd_copy_out);
	return (0);
}

int forking(t_cmd *cmd, pid_t *pid, char **av)
{
	int len;
	int i;
	t_cmd curr;

	i = 0;
	curr = *cmd;
	len = len_cmd(curr);
	while (curr)
	{
		open_fd(&curr);
		curr = curr->next;
	}
	curr = *cmd;
	if (len == 1 && is_builtin(curr->argv[0])) // !!!!!!!!!!!!!!!!!!!!!
	{
		return (no_forking(cmd, pid));
	}
	while (i < len)
	{
		multifork(pid, i, cmd, &curr);
		curr = curr->next;
		i++;
	}
	return (0);
}

int w_pid(t_cmd *cmd, pid_t *pid, char **av)
{
	t_cmd	*curr;
	int 	len;
	int 	i;

	i = 0;
	curr = *cmd;
	len = len_cmd(curr);
	if (len == 1 && is_builtin(av[0]))
	{
		return (0);
	}
	while (i < len)
	{
		waitpid(pid[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS((exit_status));
		else if (WIFSIGNALED(exit_status))
			exit_status = 128 + WTERMSIG(exit_status);
		i++;
	}
	return (0);
}

int executor(t_cmd *cmd)
{
	t_cmd	*curr;
	pid_t	*pid;
	int 	ret;

	curr = *cmd;
	fill_argv(cmd);
	ret = open_pipe(cmd);
	if (ret)
		return (ret);
	pid = malloc(sizeof(pid_t) * len_cmd(curr));
	if (pid == NULL)
		return (1);
	forking(cmd, pid, av);
	signal(SIGINT, sig_cmd2);
	signal(SIGQUIT, SIG_IGN);
	w_pid(cmd, pid, av);
	signal(SIGINT, signal_cmd2);
	signal(SIGQUIT, SIG_IGN);
	free(pid);
	return (0);
}
// ------- EXEC PART -------

// ------- MAIN PART -------

void	error_input(void)
{
	write(2, "mini$hell37: syntax error near unexpected token '|'\n", 52);
	exit_status = 2;
}

void	sig_cmd(int sig)
{
	exit_status = sig;
	if (sig == 2)
	{
		exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
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
	int ret;

	sh->cmd = NULL;
	sh->line = input;
	sh->cmd = parsing(sh->line, sh->env, &sh->last_exit);
	printf("%s\n", sh->line);
	if (input != NULL && *sh != NULL)
		ret = executor(sh->cmd);
}

int	main(int ac, char **av, char **envp)
{
	char *input;
	t_env *tmp;
	t_shell *sh;

	exit_status = 0;
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
			return (print_free(&sh));
		if (check_input(input) != 0)
			error_input();
		else
			start_exec(sh, input);
		free_end(&sh, input);
	}
}