#include "libft.h"

int	ft_strchr(const char *s, int c)
{
	int	pos;

	pos = 0;
	if (!s)
		return (-1);
	while (s[pos])
	{
		if (s[pos] == c)
			return (pos);
		pos++;
	}
	return (-1);
}
