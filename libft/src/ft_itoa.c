/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:52:50 by dmazari           #+#    #+#             */
/*   Updated: 2024/11/11 11:51:07 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (0);
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char	*ft_create(int n)
{
	char	*nbr;
	size_t	count;

	count = 0;
	if (n == 0)
	{
		nbr = malloc(2);
		if (!nbr)
			return (NULL);
	}
	else
	{
		count = ft_count(n);
		nbr = malloc(sizeof(char) * count + 1);
		if (!nbr)
			return (NULL);
	}
	return (nbr);
}

static void	ft_fill(char *nbr, int count, int n)
{
	unsigned int	nb;

	nbr[count] = 0;
	if (n < 0)
	{
		nbr[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	while (nb != 0)
	{
		count--;
		nbr[count] = '0' + (nb % 10);
		nb = nb / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		count;

	count = ft_count(n);
	nbr = ft_create(n);
	if (!nbr)
		return (NULL);
	if (n == 0)
	{
		nbr[0] = '0';
		nbr[1] = 0;
	}
	else
	{
		ft_fill(nbr, count, n);
	}
	return (nbr);
}
