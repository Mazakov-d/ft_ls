/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:50:34 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/10 23:54:47 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{
	t_context	ctx;

	ctx.args = NULL;
	ctx.tokens = NULL;
	ctx.flags_set = 0;
	parse_args(ac, av, &ctx);
	ft_ls(&ctx);
	free_ctx(&ctx, 0, NULL);
}
