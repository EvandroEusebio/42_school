/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:42:35 by ieusebio          #+#    #+#             */
/*   Updated: 2025/06/20 13:24:26 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*last;
	unsigned char	uc;

	if (!s)
		return (NULL);
	last = NULL;
	uc = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == uc)
			last = (char *)s;
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (last);
}
