/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:10:55 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:10:55 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	**ft_free(char **mas, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(mas[i]);
		i++;
	}
	free(mas);
	return (NULL);
}

int	ft_word_count(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			word++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (word);
}

char	**ft_mascpy(char **mas, int word, char const *s, char c)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	j = 0;
	p = 0;
	while (s[i] && j < word)
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			mas[j][p] = s[i];
			p++;
			i++;
		}
		mas[j][p] = '\0';
		p = 0;
		j++;
	}
	mas[j] = NULL;
	return (mas);
}

char	**ft_m_word(char **mas, int word, char const *s, char c)
{
	int	i;
	int	j;
	int	len_word;

	i = 0;
	j = 0;
	len_word = 0;
	while (s[i] && j < word)
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			len_word++;
			i++;
		}
		mas[j] = (char *)malloc(sizeof(char) * (len_word + 1));
		if (!mas[j])
			return (ft_free(mas, word));
		j++;
		len_word = 0;
	}
	return (mas);
}

char	**ft_split(char const *s, char c)
{
	char	**mas;
	int		word;

	if (!s)
		return (NULL);
	word = ft_word_count(s, c);
	mas = (char **) malloc(sizeof(char *) * (word + 1));
	if (!mas)
		return (NULL);
	mas = ft_m_word(mas, word, s, c);
	if (!mas)
		return (NULL);
	return (ft_mascpy(mas, word, s, c));
}
