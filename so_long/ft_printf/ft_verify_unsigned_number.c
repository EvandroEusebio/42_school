/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_unsigned_number.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:50:24 by ieusebio          #+#    #+#             */
/*   Updated: 2025/07/17 08:50:26 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	verify_unsigned_number(unsigned int n)
{
	char	*tempstr;
	size_t	len;

	tempstr = ft_untoa(n);
	len = ft_strlen(tempstr);
	ft_putstr_fd(tempstr, 1);
	free(tempstr);
	return (len);
}
