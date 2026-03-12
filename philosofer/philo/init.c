

#include "philo.h"

/*
** Inicializa os mutexes dos garfos.
** Cada garfo é representado por um mutex; há exatamente nb_philos garfos.
** A alocação e inicialização são validadas para evitar falhas silenciosas.
** Retorna 1 em sucesso, 0 em falha.
*/
int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
	{
		write(2, ERR_ALLOC, ft_strlen(ERR_ALLOC));
		return (0);
	}
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			write(2, ERR_MUTEX, ft_strlen(ERR_MUTEX));
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			data->forks = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

/*
** Inicializa o array de filósofos.
** Cada filósofo recebe:
**   - id único (baseado em 1)
**   - garfo esquerdo (seu próprio índice)
**   - garfo direito (o próximo no círculo, com wrap-around)
**   - ponteiro para os dados compartilhados
** O padrão de garfos circulares é fundamental para o problema dos filósofos.
** Retorna 1 em sucesso, 0 em falha.
*/
int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
	{
		write(2, ERR_ALLOC, ft_strlen(ERR_ALLOC));
		return (0);
	}
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->nb_philos;
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

/*
** Inicializa os mutexes compartilhados e os campos de controle.
** - print_mutex: garante saídas no terminal sem interrupções
** - death_mutex: protege o flag de fim de simulação
** - meal_mutex:  protege contadores de refeições e tempos
** Retorna 1 em sucesso, 0 em falha.
*/
int	init_data(t_data *data)
{
	data->simulation_end = 0;
	data->nb_full = 0;
	data->start_time = 0;
	data->forks = NULL;
	data->philos = NULL;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		write(2, ERR_MUTEX, ft_strlen(ERR_MUTEX));
		return (0);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		write(2, ERR_MUTEX, ft_strlen(ERR_MUTEX));
		pthread_mutex_destroy(&data->print_mutex);
		return (0);
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		write(2, ERR_MUTEX, ft_strlen(ERR_MUTEX));
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		return (0);
	}
	return (1);
}
