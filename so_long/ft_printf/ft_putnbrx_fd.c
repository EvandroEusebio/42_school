/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrx_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:48:25 by ieusebio          #+#    #+#             */
/*   Updated: 2025/07/17 08:48:35 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrx_fd(unsigned long n, int fd, char type)
{
	unsigned long	nb;
	char			*hexlower;
	char			*hexupper;
	int				totalletter;
	char			*value;

	hexlower = "0123456789abcdef";
	hexupper = "0123456789ABCDEF";
	nb = n;
	totalletter = 0;
	if (type == 'u')
		value = hexupper;
	else if (type == 'l')
		value = hexlower;
	if (nb > 15)
		totalletter += ft_putnbrx_fd((nb / 16), fd, type);
	ft_putchar_fd(value[nb % 16], fd);
	totalletter++;
	return (totalletter);
}
