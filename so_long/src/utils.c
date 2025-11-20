/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:14:55 by ieusebio          #+#    #+#             */
/*   Updated: 2025/11/20 10:14:56 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_strlen_without_break(const char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != '\n')
			len++;
		i++;
	}
	return (len);
}

char	*ft_strcopy(char *dest, const char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_join(char *str1, char *str2)
{
	char	*newstr;
	size_t	len1;
	size_t	len2;

	if (!str1 && !str2)
		return (NULL);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	newstr = (char *)malloc(len1 + len2 + 1);
	if (!newstr)
	{
		free(str1);
		return (NULL);
	}
	if (str1)
	{
		ft_strcopy(newstr, str1);
		free(str1);
	}
	else
		newstr[0] = 0;
	ft_strcopy(newstr + len1, str2);
	return (newstr);
}

char	*ft_strcopy_limit(const char *str, int limit)
{
	int		real_limit;
	int		i;
	char	*newstr;

	if (!str)
		return (NULL);
	real_limit = ft_strlen(str);
	if (limit >= real_limit)
		limit = real_limit - 1;
	newstr = (char *)malloc(limit + 2);
	if (!newstr)
		return (NULL);
	i = 0;
	while (i <= limit)
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[limit + 1] = '\0';
	return (newstr);
}

int	ft_occur(char *str, char c)
{
	int	i;
	int	cont_occur;

	i = 0;
	cont_occur = 0;
	while (str[i])
	{
		if (str[i] == c)
			cont_occur++;
		i++;
	}
	return (cont_occur);
}
