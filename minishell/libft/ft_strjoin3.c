/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:04:13 by akudiezo          #+#    #+#             */
/*   Updated: 2026/01/28 17:05:07 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;
	
	if (!s1 || !s2 || !s3)
		return (NULL);
	
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	
	result = (char *)malloc(len1 + len2 + len3 + 1);
	if (!result)
		return (NULL);
	
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	ft_memcpy(result + len1 + len2, s3, len3);
	result[len1 + len2 + len3] = '\0';
	
	return (result);
}
