/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_untoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:49:12 by ieusebio          #+#    #+#             */
/*   Updated: 2025/07/17 08:49:16 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	telements(size_t n)
{
	size_t	nelements;

	nelements = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		nelements++;
	}
	return (nelements);
}

static void	fillstr(char *s, long number, int isnegative, size_t nelements)
{
	if (isnegative == 1)
		s[0] = '-';
	if (number == 0)
		s[0] = '0';
	else
	{
		while (number > 0)
		{
			s[--nelements] = (number % 10) + '0';
			number /= 10;
		}
	}
}

char	*ft_untoa(unsigned int n)
{
	char	*s;
	size_t	nelements;
	int		isnegative;
	long	nb;

	nelements = 0;
	isnegative = 0;
	nb = (long)n;
	if (nb < 0)
	{
		isnegative++;
		nb *= -1;
	}
	nelements = telements(nb) + isnegative + 1;
	s = (char *)malloc(nelements * sizeof(char));
	if (!s)
		return (NULL);
	fillstr(s, nb, isnegative, nelements -1);
	s[nelements - 1] = '\0';
	return (s);
}
