#include "philo.h"

/*
** Aguarda o término de todas as threads dos filósofos e da thread monitora.
** pthread_join bloqueia até que cada thread finalize sua execução.
** Isso garante que o programa não encerre antes de todas as threads
** liberarem seus recursos, prevenindo undefined behavior.
** Retorna 1 em sucesso, 0 em falha.
*/
int	join_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	(void)monitor_thread;
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

/*
** Inicializa o last_meal_time de todos os filósofos com o start_time.
** Isso é feito logo antes de criar as threads para que o monitor
** não detecte falsa morte antes da simulação começar de fato.
*/
static void	set_start_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
}

/*
** Cria a thread monitora separada dos filósofos.
** A thread monitora roda monitor_routine em paralelo com os filósofos.
** Retorna 1 em sucesso, 0 em falha.
*/
static int	create_monitor(t_data *data, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, monitor_routine, data) != 0)
	{
		write(2, ERR_THREAD, ft_strlen(ERR_THREAD));
		return (0);
	}
	return (1);
}

/*
** Inicia a simulação criando uma thread para cada filósofo e uma thread monitora.
**
** Ordem de operações:
**   1. Registra o tempo de início global (start_time)
**   2. Inicializa last_meal_time de cada filósofo com start_time
**   3. Cria a thread monitora
**   4. Cria uma thread por filósofo
**   5. Junta (join) a thread monitora
**   6. Junta todas as threads dos filósofos
**
** Se a criação de qualquer thread falhar, a simulação é encerrada
** e os recursos são liberados de forma segura.
** Retorna 1 em sucesso, 0 em falha.
*/
int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start_time = get_time();
	set_start_meals(data);
	if (!create_monitor(data, &monitor))
		return (0);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
		{
			write(2, ERR_THREAD, ft_strlen(ERR_THREAD));
			pthread_mutex_lock(&data->death_mutex);
			data->simulation_end = 1;
			pthread_mutex_unlock(&data->death_mutex);
			pthread_join(monitor, NULL);
			join_threads(data);
			return (0);
		}
		i++;
	}
	pthread_join(monitor, NULL);
	join_threads(data);
	return (1);
}
