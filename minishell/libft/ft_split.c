/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:00:26 by akudiezo          #+#    #+#             */
/*   Updated: 2025/06/24 09:00:36 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(char const **s, char c)
{
	size_t		len;
	const char	*word;

	while (**s && **s == c)
		(*s)++;
	word = *s;
	while (**s && **s != c)
		(*s)++;
	len = *s - word;
	return (ft_substr(word, 0, len));
}

static void	*free_split(char **split, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	split = malloc((word_count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		split[i] = get_word(&s, c);
		if (!split[i])
			return (free_split(split, i));
		i++;
	}
	split[i] = NULL;
	return (split);
}
