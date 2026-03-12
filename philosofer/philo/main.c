

#include "philo.h"

/*
** Ponto de entrada do programa philo.
**
** Fluxo principal:
**   1. Valida e interpreta os argumentos da linha de comando (parse_args)
**   2. Inicializa os mutexes globais e flags de controle (init_data)
**   3. Inicializa os garfos (mutexes de cada garfo) (init_forks)
**   4. Inicializa o array de filósofos com seus atributos (init_philos)
**   5. Inicia a simulação criando as threads (start_simulation)
**   6. Libera todos os recursos ao final (free_data)
**
** Em caso de falha em qualquer etapa, os recursos já alocados são
** liberados corretamente antes de encerrar com código de erro.
**
** Retorna 0 em execução bem-sucedida, 1 em caso de erro.
*/
int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (!parse_args(argc, argv, &data))
		return (1);
	if (!init_data(&data))
		return (1);
	if (!init_forks(&data))
	{
		pthread_mutex_destroy(&data.print_mutex);
		pthread_mutex_destroy(&data.death_mutex);
		pthread_mutex_destroy(&data.meal_mutex);
		return (1);
	}
	if (!init_philos(&data))
	{
		free_data(&data);
		return (1);
	}
	if (!start_simulation(&data))
	{
		free_data(&data);
		return (1);
	}
	free_data(&data);
	return (0);
}
