/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:56:55 by dmazari           #+#    #+#             */
/*   Updated: 2024/11/16 14:19:00 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long long	nb;
	size_t		i;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((nb + (nptr[i] - '0')) * sign > (LONG_MAX / 10) + 7
			|| (nb + (nptr[i] - '0')) * sign < (LONG_MIN / 10) - 8)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)nb * sign);
}
