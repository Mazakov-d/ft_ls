/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:44:24 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/10 20:44:47 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*create_path(char *dir, char *file)
{
	char	*path;
	int		i;
	int		j;

	path = malloc(sizeof(char) * (ft_strlen(dir) + ft_strlen(file) + 2));
	if (!path)
		return (NULL);
	i = -1;
	while (dir && dir[++i])
		path[i] = dir[i];
	if (i > 0 && path[i - 1] != '/')
	{
		path[i] = '/';
		i++;
	}
	j = -1;
	while (file && file[++j])
		path[i + j] = file[j];
	path[i + j] = '\0';
	return (path);
}
