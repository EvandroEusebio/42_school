/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:54:26 by ieusebio          #+#    #+#             */
/*   Updated: 2025/06/23 12:54:33 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	quantword(char const *s, char delimiter)
{
	int		i;
	size_t	quant;

	quant = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == delimiter)
			i++;
		if (s[i] != delimiter && s[i] != 0)
		{
			quant++;
			while (s[i] != delimiter && s[i] != 0)
				i++;
		}
	}
	return (quant);
}

static char	**ft_free(char **s, size_t totalwords)
{
	size_t	i;

	i = 0;
	while (i < totalwords)
		free(s[i++]);
	free(s);
	return (NULL);
}

static size_t	wordlen(const char *s, char delimiter, int *index)
{
	size_t	len;

	len = 0;
	while (s[*index] != delimiter && s[*index] != 0)
	{
		len++;
		*index += 1;
	}
	return (len);
}

static void	fillarrstr(char const *s, char **arrstr, char delimiter,
			size_t totalword)
{
	size_t	lenword;
	int		posinicialword;
	int		i;
	size_t	index;

	i = 0;
	index = 0;
	while (s[i])
	{
		while (s[i] == delimiter)
			i++;
		if (s[i] != delimiter && s[i] != 0)
		{
			posinicialword = i;
			lenword = wordlen(s, delimiter, &i);
			arrstr[index] = (char *)malloc((lenword + 1) * sizeof(char));
			if (!arrstr[index])
				ft_free(arrstr, totalword);
			ft_strlcpy(arrstr[index], s + posinicialword, lenword + 1);
			index++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	totalword;
	char	**arrstr;

	if (!s)
		return (NULL);
	totalword = quantword(s, c);
	arrstr = (char **)malloc((totalword + 1) * sizeof(char *));
	if (!arrstr)
		return (NULL);
	fillarrstr(s, arrstr, c, totalword);
	arrstr[totalword] = NULL;
	return (arrstr);
}
