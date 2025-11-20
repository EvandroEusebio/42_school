/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:50:48 by ieusebio          #+#    #+#             */
/*   Updated: 2025/07/17 08:50:53 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>
# include "../libft/libft.h"

int		ft_printf(const char *format, ...);
int		ft_putnbrx_fd(unsigned long n, int fd, char type);
char	*ft_untoa(unsigned int n);
int		verify_char(char c);
int		verify_string(char *s);
int		verify_number(int n);
int		verify_unsigned_number(unsigned int n);
int		verify_pointer_p(unsigned long n);
int		ft_verify_c(char type, va_list list);

#endif
