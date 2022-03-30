/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:02:39 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/29 13:02:39 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !(*del))
		return ;
	(*del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*trash;

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

int	ft_lstsize(t_list *lst)
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