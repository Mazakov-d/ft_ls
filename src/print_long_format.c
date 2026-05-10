/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:44:07 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/11 01:06:27 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_l_flag(struct stat s)
{
	struct passwd	*passwd;
	struct group	*group;

	print_type(s.st_mode);
	print_permissions(s.st_mode);
	ft_printf_fd(1, "%d ", s.st_nlink);
	passwd = getpwuid(s.st_uid);
	if (!passwd)
		ft_printf_fd(1, "%d ", s.st_uid);
	else
		ft_printf_fd(1, "%s ", passwd->pw_name);
	group = getgrgid(s.st_gid);
	if (!group)
		ft_printf_fd(1, "%d	", s.st_gid);
	else
		ft_printf_fd(1, "%s	", group->gr_name);
	ft_printf_fd(1, "%d	", s.st_size);
	print_time_format(s.st_mtime);
}
