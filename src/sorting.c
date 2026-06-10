/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:44:55 by mazakov           #+#    #+#             */
/*   Updated: 2026/06/10 13:32:56 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	bubble_sort_arg(t_arg **head, int reverse)
{
	int		swapped;
	long	diff;
	t_arg	*curr;

	if (!head || !*head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		curr = *head;
		while (curr && curr->next)
		{
			diff = ft_strcmp_ignore_dot(curr->name, curr->next->name);
			if ((!reverse && diff > 0) || (reverse && diff < 0))
			{
				swap_adjacent_args(head, curr, curr->next);
				swapped = 1;
				if (curr->prev)
					curr = curr->prev;
			}
			else
				curr = curr->next;
		}
	}
}

long	get_diff(int flag, t_token *curr)
{
	long	diff;

	if (flag)
		diff = time_cmp(curr->next, curr);
	else
		diff = ft_strcmp_ignore_dot(curr->name, curr->next->name);
	return (diff);
}

void	bubble_sort_token(t_token **head, int flag, int reverse)
{
	int		swapped;
	long	diff;
	t_token	*curr;

	if (!head || !*head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		curr = *head;
		while (curr && curr->next)
		{
			diff = get_diff(flag, curr);
			if ((!reverse && diff > 0) || (reverse && diff < 0))
			{
				swap_adjacent_tokens(head, curr, curr->next);
				swapped = 1;
				if (curr->prev)
					curr = curr->prev;
			}
			else
				curr = curr->next;
		}
	}
}

int	ft_strcmp_ignore_dot(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] == '.')
		i++;
	while (s2[j] && s2[j] == '.')
		j++;
	if (!s1[i] && !s2[j])
		return (i - j);
	while (s1[i] && ft_tolower(s1[i]) == ft_tolower(s2[j]))
	{
		i++;
		j++;
	}
	return ((unsigned char)ft_tolower(s1[i])
		- (unsigned char)ft_tolower(s2[j]));
}
