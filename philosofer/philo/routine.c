

#include "philo.h"

/*
** Caso especial: filósofo único.
** Com apenas um filósofo e um garfo, ele nunca consegue pegar dois garfos,
** então ele inevitavelmente morre. Esta função simula esse comportamento:
** pega o único garfo disponível e espera até morrer.
*/
static void	lone_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_state(philo, MSG_FORK);
	ft_sleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

/*
** Executa a ação de comer de um filósofo.
** Para evitar deadlocks, filósofos com ID par pegam os garfos em ordem inversa.
** Isso quebra a simetria e previne que todos tentem pegar o mesmo garfo ao mesmo
** tempo, o que causaria deadlock circular.
**
** Estratégia anti-deadlock:
**   - Filósofos ímpares: garfo esquerdo → garfo direito
**   - Filósofos pares:   garfo direito  → garfo esquerdo
**
** Após pegar ambos os garfos, atualiza last_meal_time com mutex (meal_mutex),
** evitando condição de corrida com o monitor que lê esse valor.
*/
void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_state(philo, MSG_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_state(philo, MSG_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_state(philo, MSG_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_state(philo, MSG_FORK);
	}
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_state(philo, MSG_EAT);
	ft_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

/*
** Executa a ação de dormir de um filósofo.
** Imprime a mensagem de dormir e aguarda time_to_sleep milissegundos.
** O ft_sleep respeita o sinal de fim da simulação, saindo cedo se necessário.
*/
void	philo_sleep(t_philo *philo)
{
	print_state(philo, MSG_SLEEP);
	ft_sleep(philo->data->time_to_sleep, philo->data);
}

/*
** Executa a ação de pensar de um filósofo.
** Filósofos pensam enquanto esperam garfos ficarem disponíveis.
** Uma pequena pausa é adicionada para filósofos pares para reduzir
** contenção: permite que filósofos ímpares peguem os garfos primeiro,
** melhorando a fairness geral da simulação com número par de filósofos.
*/
void	philo_think(t_philo *philo)
{
	print_state(philo, MSG_THINK);
	if (philo->data->nb_philos % 2 != 0)
		usleep(500);
}

/*
** Rotina principal executada por cada thread de filósofo.
** O ciclo é: comer → dormir → pensar → repetir.
**
** Filósofos pares dormem um pequeno tempo antes de começar,
** para escalonar o início e evitar que todos peguem garfos simultaneamente,
** reduzindo a chance de deadlock logo na inicialização.
**
** A rotina termina quando simulation_ended() retorna verdadeiro,
** o que ocorre quando um filósofo morre ou todos comeram o suficiente.
*/
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philos == 1)
	{
		lone_philosopher(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!simulation_ended(philo->data))
	{
		philo_eat(philo);
		if (simulation_ended(philo->data))
			break ;
		philo_sleep(philo);
		if (simulation_ended(philo->data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
