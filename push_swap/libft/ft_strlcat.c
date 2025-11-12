/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:35:10 by ieusebio          #+#    #+#             */
/*   Updated: 2025/06/13 14:58:36 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	lend;
	size_t	lens;
	size_t	totalc;
	size_t	index;
	size_t	sized;

	if (!dest || !src)
		return (0);
	lend = ft_strlen(dest);
	lens = ft_strlen(src);
	if (size <= lend)
		return (lens + size);
	sized = lend;
	totalc = size - lend - 1;
	index = 0;
	while (index < totalc && src[index])
		dest[sized++] = src[index++];
	dest[sized] = '\0';
	return (lend + lens);
}
