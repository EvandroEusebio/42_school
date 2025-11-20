/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_pointer_p.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:49:52 by ieusebio          #+#    #+#             */
/*   Updated: 2025/07/17 08:49:54 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	verify_pointer_p(unsigned long n)
{
	if (n == 0)
		return (write(1, "(nil)", 5));
	ft_putstr_fd("0x", 1);
	return (ft_putnbrx_fd(n, 1, 'l') + 2);
}
