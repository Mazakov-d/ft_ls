/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:20:19 by dmazari           #+#    #+#             */
/*   Updated: 2026/04/22 21:47:14 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/* #include <string.h>
#include <bsd/string.h>
#include <stdio.h>

int main()
{
	char	dst[20];
	char	*src = "salut c'est cool";
	char	dst1[20];
	char	*src1 = "salut c'est cool";
	size_t	i = ft_strlcpy(dst, src, 20);
	size_t	i1 = strlcpy(dst1, src1, 20);

	printf("%s \n %zu \n %s \n %zu", dst, i, dst1, i1);
} */