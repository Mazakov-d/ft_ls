/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:50:06 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/10 20:50:07 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	new_arg(t_arg **curr)
{
	t_arg	*new;

	new = ft_calloc(sizeof(t_arg), 1);
	if (!new)
		return ((EXIT_FAILURE));
	if (*curr)
	{
		new->prev = *curr;
		(*curr)->next = new;
	}
	*curr = new;
	return (EXIT_SUCCESS);
}

int	add_arg_node(t_arg *curr, char *name)
{
	t_arg	*new;

	if (!name)
		return (EXIT_FAILURE);
	new = ft_calloc(sizeof(t_arg), 1);
	if (!new)
	{
		free(name);
		return (EXIT_FAILURE);
	}
	new->name = name;
	if (curr)
	{
		if (curr->next)
			curr->next->prev = new;
		new->prev = curr;
		new->next = curr->next;
		curr->next = new;
	}
	return (EXIT_SUCCESS);
}

void	remove_arg_node(t_arg **arg)
{
	t_arg	*save;

	if (arg && *arg)
	{
		if ((*arg)->prev)
			(*arg)->prev->next = (*arg)->next;
		if ((*arg)->next)
			(*arg)->next->prev = (*arg)->prev;
		if ((*arg)->name)
			free((*arg)->name);
		save = *arg;
		if ((*arg)->prev)
			*arg = (*arg)->prev;
		else
			*arg = (*arg)->next;
		free(save);
	}
}

t_arg	*get_first_arg(t_arg *curr)
{
	if (curr)
	{
		while (curr->prev)
			curr = curr->prev;
	}
	return (curr);
}

void	swap_adjacent_args(t_arg **head, t_arg *a, t_arg *b)
{
	t_arg	*prev;
	t_arg	*next;

	if (!a || !b || a->next != b)
		return ;
	prev = a->prev;
	next = b->next;
	if (prev)
		prev->next = b;
	else
		*head = b;
	if (next)
		next->prev = a;
	b->prev = prev;
	b->next = a;
	a->prev = b;
	a->next = next;
}
