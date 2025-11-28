/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:49:39 by ieusebio          #+#    #+#             */
/*   Updated: 2025/07/17 08:49:42 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	verify_number(int n)
{
	char	*tempstr;
	size_t	len;

	tempstr = ft_itoa(n);
	len = ft_strlen(tempstr);
	ft_putstr_fd(tempstr, 1);
	free(tempstr);
	return (len);
}
