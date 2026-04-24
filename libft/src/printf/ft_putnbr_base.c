/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:29:27 by dmazari           #+#    #+#             */
/*   Updated: 2026/04/22 21:41:50 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(long n, char *base)
{
	int	len;
	int	count;

	count = 0;
	len = ft_strlen(base);
	if (n < 0)
	{
		n = -n;
		count += write(1, "-", 1);
	}
	if (n >= len)
		count += ft_putnbr_base(n / len, base);
	count += write(1, &base[n % len], 1);
	return (count);
}

int	ft_putn(int n)
{
	unsigned int	nb;
	char			c;
	int				count;

	count = 0;
	if (n < 0)
	{
		count += write(1, "-", 1);
		nb = -n;
	}
	else
		nb = n;
	if (nb > 9)
		count += ft_putn(nb / 10);
	c = '0' + (nb % 10);
	count += write(1, &c, 1);
	return (count);
}

int	ft_put_p(unsigned long n, char *base, int i)
{
	unsigned int	len;
	int				count;

	if (!n)
		return (write(1, "(nil)", 5));
	count = 0;
	if (i == 0)
		count += write(1, "0x", 2);
	len = ft_strlen(base);
	if ((int)n < 0)
	{
		n = -n;
		count += write(1, "-", 1);
	}
	if (n >= len)
		count += ft_put_p(n / len, base, 2);
	count += write(1, &base[n % len], 1);
	return (count);
}
