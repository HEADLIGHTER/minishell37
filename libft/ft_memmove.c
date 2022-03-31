/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:11:12 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:11:12 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)src;
	str2 = (unsigned char *)dest;
	i = 0;
	if (str1 == str2)
		return (dest);
	if (str2 > str1)
	{
		while (n-- > 0)
		{
			str2[n] = str1[n];
		}
	}
	else
	{
		while (i < n)
		{
			str2[i] = str1[i];
			i++;
		}
	}
	return (dest);
}
