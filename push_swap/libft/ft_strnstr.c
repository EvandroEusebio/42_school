/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:29:50 by ieusebio          #+#    #+#             */
/*   Updated: 2025/06/20 13:24:07 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (!big || !little)
		return (NULL);
	if (!*little)
		return ((char *)big);
	while (i < len && big[i])
	{
		j = 0;
		while ((i + j) < len && big[i + j] == little[j])
		{
			j++;
			if (!little[j])
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
