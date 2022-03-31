/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 20:55:12 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 21:04:57 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	remove_env(t_env **env, t_env *curr, t_env *prev)
{
	if (curr == *env)
		*env = curr->next;
	else if (!curr->next)
		prev->next = NULL;
	else
		prev->next = curr->next;
	free(curr->key);
	free(curr->value);
	free(curr);
	return (0);
}

void	unset_no_argc(t_list **empty, t_list *tkn, size_t len)
{
	t_list	*curr_l;
	t_list	*prec_l;

	curr_l = *empty;
	prec_l = *empty;
	while (curr_l)
	{
		if (ft_strlen(curr_l->content) == len
			&& !ft_strncmp(curr_l->content, tkn->content, len))
		{
			ft_lstrm(empty, prec_l, curr_l);
			break ;
		}
		prec_l = curr_l;
		curr_l = curr_l->next;
	}
}

int	builtin_unset(t_env **env, t_list *tkn, t_list **empty)
{
	t_env	*prev;
	t_env	*curr;
	size_t	len;

	if (!env || !*env)
		return (-1);
	while (tkn)
	{
		len = ft_strlen(tkn->content);
		curr = *env;
		prev = *env;
		while (curr)
		{
			if (ft_strlen(curr->key) == len
				&& !ft_strncmp(curr->key, tkn->content, len))
				return (remove_env(env, curr, prev));
			prev = curr;
			curr = curr->next;
		}
		if (*empty)
			unset_no_argc(empty, tkn, len);
		tkn = tkn->next;
	}
	return (0);
}
