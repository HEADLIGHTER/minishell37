/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:05:32 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:04:43 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cnt	*init_cnt(void)
{
	t_cnt	*ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	ret->s = 0;
	ret->save = NULL;
	return (ret);
}

t_shell	*get_shell(int flag)
{
	static t_shell	*sh;

	sh = NULL;
	if (flag == PULL)
		return (sh);
	else if (flag == INIT)
	{
		sh = malloc(sizeof(t_shell));
		if (!sh)
			exit(EXIT_FAILURE);
		sh->last_exit = 0;
		sh->empty = NULL;
		return (sh);
	}
	return (NULL);
}
