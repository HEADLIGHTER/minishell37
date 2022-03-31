/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:11:25 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:11:25 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstrm(t_list **begin, t_list *prev, t_list *curr)
{
	if (curr == *begin)
		*begin = curr->next;
	else if (!curr->next)
		prev->next = NULL;
	else
		prev->next = curr->next;
	free(curr->content);
	free(curr);
}
