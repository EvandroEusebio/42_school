/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:59:56 by akudiezo          #+#    #+#             */
/*   Updated: 2025/06/14 11:59:59 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	unsigned char	character;

	s_ptr = (unsigned char *)s;
	character = (unsigned char)c;
	while (n && *s_ptr != character)
	{
		s_ptr++;
		n--;
	}
	if (n)
		return ((void *)s_ptr);
	return (NULL);
}
