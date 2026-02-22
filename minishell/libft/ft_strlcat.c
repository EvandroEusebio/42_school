/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:07:06 by akudiezo          #+#    #+#             */
/*   Updated: 2025/06/12 16:16:42 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	if (!dest && dstsize > 0)
		return (0);
	if (!src)
		return (ft_strlen(dest));
	dest_len = 0;
	src_len = ft_strlen(src);
	while (dest_len < dstsize && dest[dest_len])
		dest_len++;
	if (dest_len == dstsize)
		return (dstsize + src_len);
	i = 0;
	while (src[i] && (dest_len + i + 1 < dstsize))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (dest_len + i < dstsize)
		dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
