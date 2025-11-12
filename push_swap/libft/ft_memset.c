/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:15:49 by ieusebio          #+#    #+#             */
/*   Updated: 2025/06/23 16:27:52 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int b, size_t n)
{
	size_t			i;
	unsigned char	*r;

	if (!s)
		return (NULL);
	i = 0;
	r = (unsigned char *)s;
	while (i < n)
		r[i++] = b;
	return (s);
}
