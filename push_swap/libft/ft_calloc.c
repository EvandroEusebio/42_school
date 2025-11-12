/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:24:53 by ieusebio          #+#    #+#             */
/*   Updated: 2025/06/16 15:24:55 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*c;

	if (nmemb != 0 && (nmemb * size) / nmemb != size)
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		c = malloc(1);
		if (!c)
			return (NULL);
		ft_bzero(c, 1);
		return (c);
	}
	c = malloc(nmemb * size);
	if (!c)
		return (NULL);
	else
		ft_bzero(c, nmemb * size);
	return (c);
}
