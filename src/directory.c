/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:54:07 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/10 21:49:39 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	dir_parsing(t_context *ctx)
{
	DIR	*dir;

	errno = 0;
	dir = opendir(ctx->args->name);
	if (errno)
	{
		ft_printf_fd(2, "ft_ls: cannot access '%s': ", ctx->args->name);
		perror(NULL);
		return ;
	}
	fill_dirs_data(ctx, dir);
	return ;
}

void	fill_dirs_data(t_context *ctx, DIR *dir)
{
	struct dirent	*entry;
	char			*path;

	while ((entry = readdir(dir)))
	{
		errno = 0;
		if (is_flag_set(ctx->flags_set, A)
			|| (!is_flag_set(ctx->flags_set, A) && entry->d_name[0] != '.'))
		{
			if (new_token(&ctx->args->token))
			{
				closedir(dir);
				free_ctx(ctx, 1, "malloc failed");
			}
			ctx->args->token->type = entry->d_type;
			ctx->args->token->name = ft_strdup(entry->d_name);
			if (!ctx->args->token->name)
			{
				closedir(dir);
				free_ctx(ctx, 1, "malloc failed");
			}
			path = create_path(ctx->args->name, ctx->args->token->name);
			if (!path)
				free_ctx(ctx, 1, "malloc failed");
			lstat(path, &ctx->args->token->s);
			free(path);
			if (errno)
			{
				ft_printf_fd(2, "ft_ls: cannot access '%s': ",
					ctx->args->token->name);
				perror(NULL);
			}
			if (is_flag_set(ctx->flags_set, MR)
				&& (ctx->args->token->s.st_mode & __S_IFMT) == __S_IFDIR
				&& ft_strncmp(ctx->args->token->name, ".", 2)
				&& ft_strncmp(ctx->args->token->name, "..", 3))
				if (add_arg_node(ctx->args,
						create_path(ctx->args->name, entry->d_name), is_flag_set(ctx->flags_set, R)))
					free_ctx(ctx, 1, "malloc failed");
			ctx->args->total += ctx->args->token->s.st_blocks;
		}
	}
	closedir(dir);
	if (errno)
		perror("Readdir");
}
