/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:11:10 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:11:10 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

void	*ft_memset(void *srs, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	j;

	str = (unsigned char *)srs;
	j = (unsigned char)c;
	i = 0;
	while (n > i)
	{
		str[i] = j;
		i++;
	}
	return (str);
}
