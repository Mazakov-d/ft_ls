/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:52:35 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/10 20:52:48 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_bit(short *flags, int i)
{
	*flags = *flags | (1 << i);
}

void	set_flags(char **av, t_context *ctx, int i)
{
	int	j;

	j = 0;
	while (av[i][++j])
	{
		if (av[i][j] == 'R')
			set_bit(&ctx->flags_set, MR);
		else if (av[i][j] == 'r')
			set_bit(&ctx->flags_set, R);
		else if (av[i][j] == 'l')
			set_bit(&ctx->flags_set, L);
		else if (av[i][j] == 'a')
			set_bit(&ctx->flags_set, A);
		else if (av[i][j] == 't')
			set_bit(&ctx->flags_set, T);
		else if (av[i][j] == 'i')
			set_bit(&ctx->flags_set, I);
	}
}

int	is_flag_set(short flag, int i)
{
	return (flag & (1 << i));
}

void	no_args_given(t_context *ctx)
{
	if (new_arg(&ctx->args))
		free_ctx(ctx, 1, "malloc failed");
	ctx->args->name = ft_strdup(".");
	if (!ctx->args->name)
		free_ctx(ctx, 1, "ft_strudp failed");
}

void	parse_args(int ac, char **av, t_context *ctx)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
			set_flags(av, ctx, i);
		else
		{
			if (new_arg(&ctx->args))
				free_ctx(ctx, 1, "malloc failed");
			ctx->args->name = ft_strdup(av[i]);
			if (!ctx->args->name)
				free_ctx(ctx, 1, "ft_strdup failed");
		}
		i++;
	}
	if (!ctx->args)
		no_args_given(ctx);
	ctx->args = get_first_arg(ctx->args);
}
