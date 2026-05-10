/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:57:02 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/11 00:24:27 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	new_token(t_token **curr)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (EXIT_FAILURE);
	if (*curr)
	{
		new->prev = *curr;
		(*curr)->next = new;
	}
	*curr = new;
	return (EXIT_SUCCESS);
}

t_token	*get_first_token(t_token *curr)
{
	if (curr)
	{
		while (curr->prev)
			curr = curr->prev;
	}
	return (curr);
}

void	swap_adjacent_tokens(t_token **head, t_token *a, t_token *b)
{
	t_token	*prev;
	t_token	*next;

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

void	sort_tokens(t_token **t, short flag)
{
	*t = get_first_token(*t);
	bubble_sort_token(t, is_flag_set(flag, T), is_flag_set(flag, R));
}

int	time_cmp(t_token *t1, t_token *t2)
{
	long	diff;

	diff = t1->s.st_mtime - t2->s.st_mtime;
	if (diff != 0)
		return (diff);
	return (ft_strcmp_ignore_dot(t2->name, t1->name));
}
