/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:30:07 by akudiezo          #+#    #+#             */
/*   Updated: 2025/06/12 12:29:40 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;

	if (!dest)
		return (NULL);
	if (!src)
		return (dest);
	dest_ptr = (unsigned char *)dest;
	src_ptr = (const unsigned char *)src;
	while (n--)
		*dest_ptr++ = *src_ptr++;
	return (dest);
}
