/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:47:03 by dmazari           #+#    #+#             */
/*   Updated: 2026/04/22 21:47:14 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static	void	ft_free_all(int i, char **str)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

static	int	ft_count_words(const char *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static size_t	ft_strclen(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static	char	*ft_strsplit(const char *s, char c)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(ft_strclen(s, c) + 1);
	if (!str)
		return (NULL);
	while (s[i] && i < ft_strclen(s, c))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	**ft_split(const char *s, char c)
{
	char	**str;
	int		i;

	str = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			str[i] = ft_strsplit(s, c);
			if (!str[i])
				return (ft_free_all(i, str), NULL);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	str[i] = NULL;
	return (str);
}
