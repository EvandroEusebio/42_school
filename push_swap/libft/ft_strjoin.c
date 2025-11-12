/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:34:55 by ieusebio          #+#    #+#             */
/*   Updated: 2025/06/16 18:34:57 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	ls1;
	size_t	ls2;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	newstr = (char *)ft_calloc(ls1 + ls2 + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_strlcat(newstr, s1, ls1 + 1);
	ft_strlcat(newstr, s2, ls1 + ls2 + 1);
	return (newstr);
}
