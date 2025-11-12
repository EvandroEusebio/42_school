/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:16:04 by ieusebio          #+#    #+#             */
/*   Updated: 2025/06/20 13:22:35 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*b;
	unsigned char		r;
	size_t				i;

	if (!s)
		return (NULL);
	i = 0;
	r = (unsigned char)c;
	b = (const unsigned char *)s;
	while (i < n)
	{
		if (r == b[i])
			return ((void *)(&b[i]));
		i++;
	}
	return (NULL);
}
