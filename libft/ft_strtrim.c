/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:10:19 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:12:07 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_chek(char const *s1)
{
	char	*str;

	str = (char *) malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!str)
		return (NULL);
	str[ft_strlen(s1)] = '\0';
	return (str);
}

char	*ft_copy(size_t i, size_t j, char *str, char const *s1)
{
	size_t	l;

	l = 0;
	while (i < j)
	{
		str[l] = s1[i];
		l++;
		i++;
	}
	str[l] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	l;
	char	*str;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_chek(s1));
	j = ft_strlen(s1) - 1;
	i = 0;
	while (ft_strchr(set, s1[i]) != NULL && s1[i])
		i++;
	if (i >= ft_strlen(s1))
		return (ft_strdup(""));
	while (ft_strchr(set, s1[j]) != NULL && j != 0)
		j--;
	j++;
	l = j - i;
	str = (char *) malloc(sizeof(char) * l + 1);
	if (!str)
		return (NULL);
	return (ft_copy(i, j, str, s1));
}
