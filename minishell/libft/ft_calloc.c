/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:20:31 by akudiezo          #+#    #+#             */
/*   Updated: 2025/06/16 16:32:00 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	total_size;
	void	*new_space;

	if (num == 0 || size == 0)
		return (malloc(0));
	if (num > SIZE_MAX / size)
		return (NULL);
	total_size = num * size;
	new_space = malloc(total_size);
	if (!new_space)
		return (NULL);
	ft_bzero(new_space, total_size);
	return (new_space);
}
