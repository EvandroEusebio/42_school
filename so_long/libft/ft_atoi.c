/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:25:34 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/04/13 01:16:21 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	aux(const char *s1, int sign)
{
	int	i;
	long	res;

	i = 0;
	res = 0;
	while (s1[i] >= 48 && s1[i] <= 57)
	{
		if (sign == 1 && (res > (2147483647 - (s1[i] - '0')) / 10))
			return (-1);
		if (sign == -1 && (res > (2147483648 - (s1[i] - '0')) / 10))
			return (0);
		res = (res * 10) + (s1[i] - '0');
		i++;
	}
	return ((int)(res * sign));
}

int	ft_atoi(const char *str)
{
	int		minus;
	int	contsignal;
	int	i;

	minus = 1;
	i = 0;
	contsignal = 0;
	if (!str)
		return (0);
	while (str[i] > 0 && str[i] <= 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		contsignal++;
		i++;
	}
	if (contsignal > 1)
		return (0);
	return (aux(str + i, minus));
}
