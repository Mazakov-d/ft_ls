/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:51:45 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/11 00:41:19 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	rewind_ctx(t_context *ctx)
{
	if (ctx)
	{
		ctx->tokens = get_first_token(ctx->tokens);
		ctx->args = get_first_arg(ctx->args);
	}
}

void	free_tokens(t_token *tokens)
{
	void	*save;

	tokens = get_first_token(tokens);
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

	args = get_first_arg(args);
	while (args)
	{
		if (args->name)
			free(args->name);
		if (args->sub_dir)
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
