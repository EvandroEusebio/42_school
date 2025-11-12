/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:33:32 by ieusebio          #+#    #+#             */
/*   Updated: 2025/06/16 16:37:19 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = (char *)malloc(len * (sizeof(char)));
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s, len);
	return (dup);
}
