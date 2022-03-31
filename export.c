/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:08:56 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 21:15:00 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	built_no_argv(t_env *env, t_list *empty)
{
	while (env)
	{
		if (env->set)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	while (empty)
	{
		printf("%s\n", (char *)empty->content);
		empty = empty->next;
	}
}

t_list	*lst_comp(t_list *one, t_list *two)
{
	t_list	*prev;

	prev = one;
	while (one)
	{
		if (!ft_strcmp(one->content, two->content))
			return (prev);
		prev = one;
		one = one->next;
	}
	return (NULL);
}

static void	new_key(t_list *tkn, t_list **empty)
{
	if (*empty)
	{
		if (!lst_comp(*empty, tkn))
			ft_lstadd_back(empty, ft_lstnew(ft_strdup(tkn->content)));
	}
	else
		ft_lstadd_back(empty, ft_lstnew(ft_strdup(tkn->content)));
}

static void	handle_logic(t_env *env, t_list *tkn, t_list **empty)
{
	int		i;
	t_env	*tmp;
	t_list	*prev;

	if (!is_var_declarat(tkn->content))
		return (mas3(tkn->content));
	i = find_char(tkn->content, '=');
	if (((char *)tkn->content)[i] == '=')
	{
		prev = lst_comp(*empty, tkn);
		if (prev && *empty)
		{
			if (prev == *empty)
				ft_lstrm(empty, prev, prev);
			else
				ft_lstrm(empty, prev, prev->next);
		}
		tmp = env_new(ft_substr(tkn->content, 0, i),
				ft_substr(tkn->content, i + 1,
					ft_strlen(tkn->content + i + 1)), 1);
		envp_back(&env, tmp);
	}
	else
		new_key(tkn, empty);
}

int	built_in_export(t_env *env, t_list *tkn, t_list **empty)
{
	t_env	*tmp;

	if (!tkn)
		built_no_argv(env, *empty);
	while (tkn)
	{
		tmp = get_env(env, tkn->content);
		if (tmp)
		{
			if (is_var_declaration(tkn->content))
				env_value(tmp, tkn->content);
			tmp->set = 1;
		}
		else
			handle_logic(env, tkn, empty);
		tkn = tkn->next;
	}
	return (0);
}
