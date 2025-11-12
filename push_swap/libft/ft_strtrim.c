/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:40:52 by ieusebio          #+#    #+#             */
/*   Updated: 2025/06/17 10:40:54 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	aux(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		ini;
	size_t		len;
	size_t		sizet;
	char		*scpy;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	ini = 0;
	while (ini < len && aux(s1[ini], set))
		ini++;
	while (len > ini && aux(s1[len - 1], set))
		len--;
	sizet = len - ini;
	scpy = (char *)malloc(sizet + 1);
	if (scpy == NULL)
		return (NULL);
	ft_strlcpy(scpy, s1 + ini, sizet + 1);
	return (scpy);
}
