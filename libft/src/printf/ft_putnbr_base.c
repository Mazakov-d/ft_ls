/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:29:27 by dmazari           #+#    #+#             */
/*   Updated: 2026/05/06 14:22:22 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_fd(long n, char *base, int fd)
{
	int	len;
	int	count;

	count = 0;
	len = ft_strlen(base);
	if (n < 0)
	{
		n = -n;
		count += write(fd, "-", 1);
	}
	if (n >= len)
		count += ft_putnbr_base_fd(n / len, base, fd);
	count += write(fd, &base[n % len], 1);
	return (count);
}

int	ft_putn_fd(int n, int fd)
{
	unsigned int	nb;
	char			c;
	int				count;

	count = 0;
	if (n < 0)
	{
		count += write(fd, "-", 1);
		nb = -n;
	}
	else
		nb = n;
	if (nb > 9)
		count += ft_putn_fd(nb / 10, fd);
	c = '0' + (nb % 10);
	count += write(fd, &c, 1);
	return (count);
}

int	ft_put_p_fd(unsigned long n, char *base, int i, int fd)
{
	unsigned int	len;
	int				count;

	if (!n)
		return (write(fd, "(nil)", 5));
	count = 0;
	if (i == 0)
		count += write(fd, "0x", 2);
	len = ft_strlen(base);
	if ((int)n < 0)
	{
		n = -n;
		count += write(fd, "-", 1);
	}
	if (n >= len)
		count += ft_put_p_fd(n / len, base, 2, fd);
	count += write(1, &base[n % len], 1);
	return (count);
}
