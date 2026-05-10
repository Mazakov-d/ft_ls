/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:54:07 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/10 23:54:41 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	close_dir_exit(t_context *ctx, DIR *dir)
{
	closedir(dir);
	free_ctx(ctx, 1, "malloc failed");
}

void	dir_parsing(t_context *ctx, t_arg *arg)
{
	DIR	*dir;

	errno = 0;
	dir = opendir(arg->name);
	if (errno)
	{
		ft_printf_fd(2, "ft_ls: cannot access '%s': ", arg->name);
		perror(NULL);
		return ;
	}
	fill_dirs_data(ctx, arg, dir);
	return ;
}

void	sub_directories_call(t_context*ctx, t_arg *arg)
{
	if (arg)
	{
		while (arg->token)
		{
			if ((arg->token->s.st_mode & __S_IFMT) == __S_IFDIR
				&& ft_strncmp(arg->token->name, ".", 2)
				&& ft_strncmp(arg->token->name, "..", 3))
			{
				if (add_arg_node(&arg->sub_dir,
						create_path(arg->name, arg->token->name)))
					free_ctx(ctx, 1, "malloc failed");
				dir_parsing(ctx, arg->sub_dir);
			}
			if (!arg->token->next)
				break ;
			arg->token = arg->token->next;
		}
		arg->sub_dir = get_first_arg(arg->sub_dir);
		arg->token = get_first_token(arg->token);
	}
}

void	get_stat_file(t_context *ctx, t_arg *arg, DIR *dir)
{
	char	*path;

	path = create_path(arg->name, arg->token->name);
	if (!path)
		close_dir_exit(ctx, dir);
	lstat(path, &arg->token->s);
	free(path);
	if (errno)
	{
		ft_printf_fd(2, "ft_ls: cannot access '%s': ",
			arg->token->name);
		perror(NULL);
		errno = 0;
	}
	arg->total += arg->token->s.st_blocks;
}

void	fill_dirs_data(t_context *ctx, t_arg *arg, DIR *dir)
{
	struct dirent	*entry;

	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		errno = 0;
		if (!is_flag_set(ctx->flags_set, A) && entry->d_name[0] == '.')
			continue ;
		if (new_token(&arg->token))
			close_dir_exit(ctx, dir);
		arg->token->type = entry->d_type;
		arg->token->name = ft_strdup(entry->d_name);
		if (!arg->token->name)
			close_dir_exit(ctx, dir);
		get_stat_file(ctx, arg, dir);
	}
	closedir(dir);
	if (errno)
		perror("Readdir");
	sort_tokens(&arg->token, ctx->flags_set);
	if (is_flag_set(ctx->flags_set, MR))
		sub_directories_call(ctx, arg);
}
