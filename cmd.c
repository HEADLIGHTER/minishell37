#include "minishell.h"

t_cmd *cmd_new(void)
{
	t_cmd *new;

	new = malloc(sizeof (*new));
	if (!new)
	{
		ft_putstr_fd("mini$hell37: malloc:", 2);
		ft_putstr_fd(strerror(ENOMEM), 2);
		return (NULL);
	}
	new->token = NULL;
	new->file_in = NULL;
	new->file_out = NULL;
	new->std_in = STDIN_FILENO;
	new->std_out = STDOUT_FILENO;
	new->fd_copy_in = STDIN_FILENO;
	new->fd_copy_out = STDOUT_FILENO;
	new->p_in[0] = -1;
	new->p_in[1] = -1;
	new->p_out[0] = -1;
	new->p_out[1] = -1;
	new->append = 0;
	new->next = NULL;
	return (new);
}
t_cmd *cmd_last(t_cmd **cmd)
{
	t_cmd *cur;

	if (!cmd || !*cmd)
		return (NULL);
	cur = *cmd;
	while (cur->next)
		cur = cur->next;
	return (cur);
}
void tkn_back(t_cmd **begin, char *cntnt)
{
	t_list *new;
	t_cmd *cmd;

	new = ft_lstnew(cntnt);
	if (!begin || !new)
	{
		free(new);
		return ;
	}
	cmd = cmd_last(begin);
	ft_lstadd_back(&cmd->token, new);
}

void cmd_back(t_cmd **cmd, char *id)
{
	t_cmd *new;
	t_cmd *cur;

	new = cmd_new();
	if (!cmd || !new)
	{
		free(new);
		return ;
	}
	tkn_back(&new, id);
	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	cur = cmd_last(cmd);
	cur->next = new;
}

