/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:09:53 by dmazari           #+#    #+#             */
/*   Updated: 2026/04/22 21:42:26 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_called_printf(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int)));
	if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	if (c == 'p')
		return (ft_put_p(va_arg(ap, unsigned long), "0123456789abcdef", 0));
	if (c == 'd' || c == 'i')
		return (ft_putn(va_arg(ap, int)));
	if (c == 'u')
		return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789"));
	if (c == 'x')
		return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF"));
	if (c == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	size_t	i;
	int		count;
	int		tmp;

	if (write(1, 0, 0) == -1 || !fmt)
		return (-1);
	count = 0;
	i = 0;
	va_start(ap, fmt);
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			tmp = ft_called_printf(fmt[++i], ap);
			if (tmp == -1)
				return (va_end(ap), -1);
			count += tmp;
		}
		else
			count += ft_putchar(fmt[i]);
		i++;
	}
	va_end(ap);
	return (count);
}
