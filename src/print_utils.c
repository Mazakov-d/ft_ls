/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:57:44 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/10 20:57:45 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	condition_print(int condition, char *true, char *false)
{
	if (condition)
		ft_printf_fd(1, "%s", true);
	else
		ft_printf_fd(1, "%s", false);
}

void	print_type(int mode)
{
	int	value;

	value = mode & __S_IFMT;
	if (__S_IFBLK == value)
		ft_printf_fd(1, "b");
	else if (__S_IFCHR == value)
		ft_printf_fd(1, "c");
	else if (__S_IFDIR == value)
		ft_printf_fd(1, "d");
	else if (__S_IFIFO == value)
		ft_printf_fd(1, "p");
	else if (__S_IFLNK == value)
		ft_printf_fd(1, "l");
	else if (__S_IFREG == value)
		ft_printf_fd(1, "-");
	else if (__S_IFSOCK == value)
		ft_printf_fd(1, "s");
	else
		ft_printf_fd(1, "?");
}

void	print_permissions(int permissions)
{
	condition_print(permissions & S_IRUSR, "r", "-");
	condition_print(permissions & S_IWUSR, "w", "-");
	condition_print(permissions & S_IXUSR, "x", "-");
	condition_print(permissions & S_IRGRP, "r", "-");
	condition_print(permissions & S_IWGRP, "w", "-");
	condition_print(permissions & S_IXGRP, "x", "-");
	condition_print(permissions & S_IROTH, "r", "-");
	condition_print(permissions & S_IWOTH, "w", "-");
	condition_print(permissions & S_IXOTH, "x", "-");
	ft_printf_fd(1, " ");
}

void	print_time_format(long t)
{
	char	*c_time;
	time_t	time;
	int		count;
	int		i;

	time = t;
	count = 0;
	i = 3;
	c_time = ctime(&time);
	if (!c_time)
	{
		ft_printf_fd(1, "time_error ");
		return ;
	}
	while (c_time[++i])
	{
		if (c_time[i] == ':')
			count++;
		if (c_time[i] == ':' && count > 1)
		{
			ft_printf_fd(1, " ");
			return ;
		}
		ft_printf_fd(1, "%c", c_time[i]);
	}
}
