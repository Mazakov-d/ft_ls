/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:16:38 by dmazari           #+#    #+#             */
/*   Updated: 2026/04/22 21:47:14 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i_big;
	size_t	i_little;
	size_t	save;

	if (!little[0])
		return ((char *)big);
	i_big = 0;
	while (big[i_big] && i_big < len)
	{
		i_little = 0;
		if (big[i_big] == little[i_little])
		{
			save = i_big;
			while (big[i_big + i_little] == little[i_little]
				&& big[i_big + i_little] && little[i_little]
				&& i_big + i_little < len)
				i_little++;
			if (!little[i_little])
				return ((char *)big + save);
		}
		i_big++;
	}
	return (NULL);
}
/* int	main()
{
	char	*big = "";
	char	*little = "";
	size_t	len = 10;

	printf("%s", ft_strnstr(big, little, len));
} */