/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:49:15 by dmazari           #+#    #+#             */
/*   Updated: 2026/04/22 21:47:14 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*a;

	i = 0;
	if (size != 0 && nmemb > __SIZE_MAX__ / size)
		return (NULL);
	a = malloc(nmemb * size);
	if (!a)
		return (NULL);
	while (i < nmemb * size)
	{
		*(char *)(a + i) = 0;
		i++;
	}
	return (a);
}
