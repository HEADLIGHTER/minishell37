#include "minishell.h"

//int exit_status;
//
//int	free_all(t_shell **sh)
//{
//	return (1);
//}

//int	print_free(t_shell **sh)
//{
//	printf("exit\n");
//	//clean_env();
//	return (free_all(sh));
//}
//void	free_end(t_shell **sh, char *input)
//{
//	if (input)
//		free(input);
//	free_all(sh);
//}
int exit_status;
// ------- FREE PART -------






void	free_end(t_shell *sh, char *input)
{
//	if (input)
//		free(input);
	free_all(sh);
}





// ------- FREE PART -------

// ------- EXEC PART -------

// *** freex ***


// *** freex ***
// *** utils ***







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






// *** pipe ***


// *** pipe ***

// *** fdes ***



// *** fdes ***
// *** exist ***



// *** exist ***
















// ------- EXEC PART -------

// ------- MAIN PART -------



//void	sig_cmd(int sig)
//{
//	if (sig == 2)
//	{
//		printf("\n");
//		rl_on_new_line();
//		rl_redisplay();
//	}
//	if (sig == SIGQUIT)
//	{
//		write(2, "Quit (core dumped)\n", 19);
//		exit (1);
//	}
//}







