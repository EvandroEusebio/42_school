/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:18:17 by ieusebio          #+#    #+#             */
/*   Updated: 2025/06/19 14:18:19 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	index;

	if (!s)
		return ;
	index = 0;
	while (s[index])
		write(fd, &s[index++], 1);
	write(fd, "\n", 1);
}
