/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:33:39 by akudiezo          #+#    #+#             */
/*   Updated: 2025/06/13 15:15:41 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_ptr;
	char	target;

	s_ptr = (char *)s;
	target = (char)c;
	while (*s_ptr)
	{
		if (*s_ptr == target)
			return (s_ptr);
		s_ptr++;
	}
	if (target == '\0')
		return (s_ptr);
	return (NULL);
}
