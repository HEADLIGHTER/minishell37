/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:01:34 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/29 13:01:34 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	is_var_declaration(char *str)
{
	size_t	i;

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

static int	handle_logic(t_list *tkn, t_env *env, t_env **new)
{
	size_t	i;
	t_env	*tmp;

	tmp = get_env(env, tkn->content);
	if (!is_var_declaration(tkn->content))
	{
		free_env(*new);
		return (1);
	}
	else if ((get_env(env, tkn->content)) || (get_env(*new, tkn->content)))
		env_value(tmp, tkn->content);
	else
	{
		i = find_char(tkn->content, '=');
		tmp = env_new(ft_substr(tkn->content, 0, i),
				ft_substr(tkn->content, i + 1,
					ft_strlen(tkn->content + i + 1)), 0);
		envp_back(new, tmp);
	}
	return (0);
}

void	parse_var_declaration(t_cmd *cmd, t_list **tk, t_env *env)
{
	t_list	*tkn;
	t_env	*new;

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
	envp_back(&env, new);
}

void	executor(t_cmd *cmd, t_shell *sh)
{
	char		*path;
	struct stat	buf;

	while (cmd)
	{
		if (cmd->token && is_var_declaration(cmd->token->content))
			parse_var_declaration(cmd, &cmd->token, sh->env);
		open_fd(cmd);
		if (cmd->token && cmd->std_in != -1)
		{
			if (is_builtin(cmd->token->content))
				handel_built_in(sh, cmd, cmd->token);
			else if (!(get_bin(sh->env, cmd->token->content)))
				no_path(cmd, sh);
			else
			{
				path = get_bin(sh->env, cmd->token->content);
				execve_fct(sh, cmd, path);
			}
		}
		reset_fd(cmd);
		cmd = cmd->next;
	}
	free_cmd(sh->cmd); // TODO при утечки проверить
}
