/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:37:49 by ieusebio          #+#    #+#             */
/*   Updated: 2025/07/17 10:37:51 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_verify_c(char type, va_list list)
{
	int	len;

	len = 0;
	if (type == 'c')
		len += verify_char(va_arg(list, int));
	else if (type == 's')
		len += verify_string(va_arg(list, char *));
	else if (type == 'd' || type == 'i')
		len += verify_number(va_arg(list, int));
	else if (type == 'u')
		len += verify_unsigned_number(va_arg(list, unsigned int));
	else if (type == 'x')
		len += ft_putnbrx_fd(va_arg(list, unsigned int), 1, 'l');
	else if (type == 'X')
		len += ft_putnbrx_fd(va_arg(list, unsigned int), 1, 'u');
	else if (type == 'p')
		len += verify_pointer_p(va_arg(list, unsigned long));
	else if (type == '%')
	{
		len++;
		ft_putchar_fd('%', 1);
	}
	return (len);
}
