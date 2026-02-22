/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:59:53 by akudiezo          #+#    #+#             */
/*   Updated: 2025/06/16 16:09:05 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*new_str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	new_str = (char *)malloc(s_len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s, s_len);
	new_str[s_len] = '\0';
	return (new_str);
}
