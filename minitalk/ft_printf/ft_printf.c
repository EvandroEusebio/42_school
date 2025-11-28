/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:37:04 by ieusebio          #+#    #+#             */
/*   Updated: 2025/07/17 10:37:11 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		totalchar;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	totalchar = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			totalchar += ft_verify_c(*format, args);
			format++;
		}
		else
		{
			totalchar++;
			ft_putchar_fd(*(format++), 1);
		}
	}
	va_end(args);
	return (totalchar);
}
