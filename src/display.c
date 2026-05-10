/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:43:32 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/10 21:11:09 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	token_print(t_token *tokens, short flags_set, t_arg *args)
{
	while (tokens)
	{
		if (is_flag_set(flags_set, I))
			ft_printf_fd(1, "%d ", tokens->s.st_ino);
		if (is_flag_set(flags_set, L))
			print_l_flag(tokens->s);
		ft_printf_fd(1, "%s", tokens->name);
		if (!tokens->next)
		{
			ft_printf_fd(1, "\n");
			if (args && args->token)
				ft_printf_fd(1, "\n");
			break ;
		}
		else if (is_flag_set(flags_set, L))
			ft_printf_fd(1, "\n");
		else
			ft_printf_fd(1, "  ");
		tokens = tokens->next;
	}
}

void	ls_print(t_context *ctx)
{
	ctx->args = get_first_arg(ctx->args);
	bubble_sort_arg(&ctx->args, is_flag_set(ctx->flags_set, R));
	sort_tokens(&ctx->tokens, ctx->flags_set);
	token_print(ctx->tokens, ctx->flags_set, ctx->args);
	while (ctx->args)
	{
		if (ctx->args->token)
		{
			sort_tokens(&ctx->args->token, ctx->flags_set);
			if (ctx->args->next || ctx->args->prev)
				ft_printf_fd(1, "%s:\n", ctx->args->name);
			if (is_flag_set(ctx->flags_set, L))
				ft_printf_fd(1, "total %d\n", ctx->args->total / 2);
			token_print(ctx->args->token, ctx->flags_set, NULL);
		}
		if (!ctx->args->next)
			break ;
		if (ctx->args->token)
			ft_printf_fd(1, "\n", ctx->args->name);
		ctx->args = ctx->args->next;
	}
}
