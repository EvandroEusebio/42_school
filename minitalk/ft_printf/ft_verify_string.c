/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:50:11 by ieusebio          #+#    #+#             */
/*   Updated: 2025/07/17 08:50:13 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	verify_string(char *s)
{
	char	*tempstr;
	size_t	len;

	if (!s)
		return (write(1, "(null)", 6));
	tempstr = ft_strdup(s);
	len = ft_strlen(tempstr);
	ft_putstr_fd(tempstr, 1);
	free(tempstr);
	return (len);
}
