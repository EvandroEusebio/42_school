
#include "philo.h"

/*
** Destrói todos os mutexes alocados durante a inicialização.
** A ordem de destruição é:
**   1. Mutexes dos garfos (se alocados)
**   2. Mutex de impressão
**   3. Mutex de morte
**   4. Mutex de refeições
**
** Verificações de NULL evitam tentativas de destruir mutexes
** que nunca foram inicializados (em caso de falha parcial no init).
*/
void	destroy_mutexes(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
}

/*
** Libera toda a memória alocada dinamicamente e destrói os mutexes.
** Esta função é chamada ao final da execução do programa para garantir
** que não haja vazamentos de memória (detectáveis com Valgrind ou fsanitize).
**
** Ordem de liberação:
**   1. Destruição dos mutexes (garfos e globais)
**   2. Liberação do array de garfos
**   3. Liberação do array de filósofos
**
** Os mutexes devem ser destruídos ANTES de liberar o ponteiro do array,
** pois destroy_mutexes precisa do ponteiro ainda válido para iterar.
*/
void	free_data(t_data *data)
{
	destroy_mutexes(data);
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
