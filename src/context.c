/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:51:45 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/10 22:49:18 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	rewind_ctx(t_context *ctx)
{
	if (ctx)
	{
		ctx->tokens = get_first_token(ctx->tokens);
		ctx->args = get_first_arg(ctx->args);
		while (ctx->args)
		{
			ctx->args->token = get_first_token(ctx->args->token);
			if (!ctx->args->next)
				break ;
			ctx->args = ctx->args->next;
		}
		ctx->args = get_first_arg(ctx->args);
	}
}

void	free_tokens(t_token *tokens)
{
	void	*save;

	while (tokens)
	{
		if (tokens->name)
			free(tokens->name);
		save = tokens;
		tokens = tokens->next;
		free(save);
	}
}

void	free_args(t_arg *args)
{
	void	*save;

	while (args)
	{
		if (args->name)
			free(args->name);
		args->sub_dir = get_first_arg(args->sub_dir);
		free_args(args->sub_dir);
		free_tokens(args->token);
		save = args;
		args = args->next;
		free(save);
	}
}

void	free_ctx(t_context *ctx, int ret, char *error)
{
	if (error)
		ft_printf_fd(2, "Error: %s\n", error);
	if (ctx)
	{
		rewind_ctx(ctx);
		free_tokens(ctx->tokens);
		free_args(ctx->args);
	}
	exit(ret);
}
