/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:38:06 by akudiezo          #+#    #+#             */
/*   Updated: 2025/06/16 15:47:40 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s_ptr;

	if (!s || c == 0)
		return ((char *)(s + ft_strlen(s)));
	if (c > 126)
		return ((char *)s);
	s_ptr = NULL;
	while (*s)
	{
		if (*s == c)
			s_ptr = (char *)s;
		s++;
	}
	return (s_ptr);
}
