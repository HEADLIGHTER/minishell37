/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:11:46 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:12:07 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isinset(int c, char *set)
{
	size_t	i;

	i = 0;
	if (!c)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		++i;
	}
	return (0);
}
