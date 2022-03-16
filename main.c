#include "minishell.h"

int exit_status;

int	free_all(t_shell **sh)
{
	return (1);
}

int	print_free(t_shell **sh)
{
	printf("exit\n");
	//clean_env();
	return (free_all(sh));
}
void	free_end(t_shell **sh, char *input)
{
	if (input)
		free(input);
	free_all(sh);
}

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

void	start_exec(t_shell **sh, char *input)
{
	sh->cmd = NULL;
	sh->line = input;
	sh->cmd = parsing(sh->line, sh->env, &sh->last_exit);
	printf("%s\n", sh->line);
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
			start_exec(&sh, input);
		free_end(&sh, input);
	}
}