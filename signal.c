#include "minishell.h"

t_cnt       *init_cnt(void)
{
	t_cnt *ret;

	if (!(ret = malloc(sizeof(*ret))))
		return (NULL);
	ret->s = 0;
	ret->save = NULL;
	return (ret);
}

t_shell *get_shell(int flag)
{
	static t_shell *sh = NULL;

	if (flag == PULL)
		return (sh);
	else if (flag == INIT)
	{
		if (!(sh = malloc(sizeof(t_shell))))
			exit(EXIT_FAILURE);
//		init_terminal(sh);
		//sh->hst_path = NULL;
//		sh->term_key = init_termcap();
		//sh->spc = init_cnt();
		sh->last_exit = 0;
		return (sh);
	}
	return (NULL);
}