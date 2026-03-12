#include "philo.h"

/*
** Verifica se todos os caracteres de uma string são dígitos numéricos.
** Também rejeita strings vazias ou com sinal negativo.
** Retorna 1 se válido, 0 se inválido.
*/
int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/*
** Verifica se todos os argumentos são números válidos e positivos.
** Também valida que o número de filósofos está dentro dos limites.
** Retorna 1 se tudo está válido, 0 caso contrário.
*/
static int	validate_all(int argc, char **argv)
{
	int			i;
	long long	val;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			write(2, ERR_ARGS, ft_strlen(ERR_ARGS));
			return (0);
		}
		val = ft_atoll(argv[i]);
		if (val <= 0 || val > INT_MAX)
		{
			write(2, ERR_ARGS, ft_strlen(ERR_ARGS));
			return (0);
		}
		i++;
	}
	return (1);
}

/*
** Realiza o parse dos argumentos da linha de comando
** e popula a estrutura t_data com os valores correspondentes.
** O quinto argumento (nb_must_eat) é opcional; se ausente, vale -1.
** Retorna 1 em caso de sucesso, 0 em caso de erro.
*/
int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		write(2, ERR_ARGS, ft_strlen(ERR_ARGS));
		return (0);
	}
	if (!validate_all(argc, argv))
		return (0);
	data->nb_philos = (int)ft_atoll(argv[1]);
	data->time_to_die = ft_atoll(argv[2]);
	data->time_to_eat = ft_atoll(argv[3]);
	data->time_to_sleep = ft_atoll(argv[4]);
	data->nb_must_eat = -1;
	if (argc == 6)
	{
		data->nb_must_eat = (int)ft_atoll(argv[5]);
		if (data->nb_must_eat <= 0)
		{
			write(2, ERR_ARGS, ft_strlen(ERR_ARGS));
			return (0);
		}
	}
	if (data->nb_philos < MIN_PHILOS || data->nb_philos > MAX_PHILOS)
	{
		write(2, ERR_ARGS, ft_strlen(ERR_ARGS));
		return (0);
	}
	return (1);
}
