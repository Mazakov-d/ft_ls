/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:43:32 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/11 00:23:39 by mazakov          ###   ########.fr       */
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

void	arg_print(t_arg *arg, short flags_set)
{
	while (arg)
	{
		if (arg->token)
		{
			if (arg->next || arg->prev
				|| is_flag_set(flags_set, MR))
				ft_printf_fd(1, "%s:\n", arg->name);
			if (is_flag_set(flags_set, L))
				ft_printf_fd(1, "total %d\n", arg->total / 2);
			token_print(arg->token, flags_set, NULL);
		}
		if (arg->sub_dir)
		{
			ft_printf_fd(1, "\n");
			arg_print(arg->sub_dir, flags_set);
		}
		if (!arg->next)
			break ;
		if (arg->token)
			ft_printf_fd(1, "\n", arg->name);
		arg = arg->next;
	}
}

void	ls_print(t_context *ctx)
{
	ctx->args = get_first_arg(ctx->args);
	sort_tokens(&ctx->tokens, ctx->flags_set);
	token_print(ctx->tokens, ctx->flags_set, ctx->args);
	arg_print(ctx->args, ctx->flags_set);
}
