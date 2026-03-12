

#include "philo.h"

/*
** Verifica se algum filósofo ultrapassou o tempo máximo sem comer.
** Itera por todos os filósofos e compara o tempo atual com o tempo
** da última refeição mais time_to_die.
**
** Se um filósofo morreu:
**   1. Define simulation_end = 1 (com death_mutex)
**   2. Imprime a mensagem de morte (com print_mutex)
**
** A impressão da morte usa print_mutex para garantir atomicidade
** e não interferir com impressões de outros filósofos.
** Retorna 1 se houve morte, 0 caso contrário.
*/
int	check_death(t_data *data)
{
	int			i;
	long long	elapsed;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		elapsed = get_time() - data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->meal_mutex);
		if (elapsed >= data->time_to_die)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->simulation_end = 1;
			pthread_mutex_unlock(&data->death_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d %s\n",
				get_time() - data->start_time,
				data->philos[i].id,
				MSG_DIED);
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** Verifica se todos os filósofos já comeram o número mínimo de refeições.
** Apenas relevante quando nb_must_eat foi fornecido pelo usuário (>= 0).
**
** Se todos saciaram, define simulation_end = 1 e retorna 1.
** Retorna 0 caso contrário ou se nb_must_eat não foi definido.
*/
int	check_all_ate(t_data *data)
{
	int	i;
	int	full_count;

	if (data->nb_must_eat == -1)
		return (0);
	full_count = 0;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten >= data->nb_must_eat)
			full_count++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (full_count == data->nb_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

/*
** Rotina principal da thread monitora.
** Roda em loop contínuo, verificando a cada 1ms:
**   1. Se algum filósofo morreu (check_death)
**   2. Se todos os filósofos já comeram o suficiente (check_all_ate)
**
** O intervalo de 1ms é um compromisso entre precisão de detecção
** e uso de CPU. Valores menores aumentam a precisão mas consomem mais CPU.
** Quando qualquer condição de parada é detectada, a thread termina.
*/
void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!simulation_ended(data))
	{
		if (check_death(data))
			return (NULL);
		if (check_all_ate(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
