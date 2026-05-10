/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:47:44 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/10 21:52:27 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	handle_file_as_arg(t_context *ctx, struct stat s)
{
	if (new_token(&ctx->tokens))
		free_ctx(ctx, 1, "malloc failed");
	ctx->tokens->name = ctx->args->name;
	ctx->tokens->s = s;
	ctx->args->name = NULL;
	remove_arg_node(&ctx->args);
}

void	ft_ls(t_context *ctx)
{
	struct stat	s;

	while (ctx->args)
	{
		errno = 0;
		lstat(ctx->args->name, &s);
		if (errno)
		{
			ft_printf_fd(2, "ft_ls: cannot access '%s': ", ctx->args->name);
			perror(NULL);
		}
		else
		{
			if ((s.st_mode & __S_IFMT) != __S_IFDIR)
			{
				handle_file_as_arg(ctx, s);
				continue ;
			}
			dir_parsing(ctx);
		}
		if (!ctx->args || !ctx->args->next)
			break ;
		ctx->args = ctx->args->next;
	}
	ls_print(ctx);
}
