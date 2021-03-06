/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:11:23 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:11:23 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned const char	*str1;
	unsigned char		*str2;
	size_t				i;
	unsigned char		stop;

	str1 = (unsigned char *)src;
	str2 = (unsigned char *)dest;
	i = 0;
	stop = (unsigned char)c;
	while (i < n)
	{
		str2[i] = str1[i];
		if (str1[i] == stop)
		{
			i++;
			return ((void *)str2 + i);
		}
		i++;
	}
	return (NULL);
}
