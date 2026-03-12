/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <42student@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2026/03/10 00:00:00 by 42student        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Retorna o tamanho de uma string (equivalente a strlen da libc).
** Necessário para uso interno sem depender de outras bibliotecas.
*/
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
** Converte uma string em long long (equivalente a atoll).
** Assume que a string foi validada previamente (apenas dígitos).
** Não lida com sinais negativos por design da validação dos argumentos.
*/
long long	ft_atoll(char *str)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

/*
** Retorna o tempo atual em milissegundos desde a época Unix.
** Utiliza gettimeofday para precisão de microssegundos convertida.
*/
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

/*
** Implementa um sleep preciso verificando o tempo constantemente.
** Diferente do usleep padrão, respeita sinalizações de fim da simulação,
** evitando que filósofos "dormam" além do necessário após uma morte.
** duration é em milissegundos.
*/
void	ft_sleep(long long duration, t_data *data)
{
	long long	start;

	start = get_time();
	while (!simulation_ended(data))
	{
		if ((get_time() - start) >= duration)
			break ;
		usleep(100);
	}
}

/*
** Imprime o estado atual de um filósofo de forma thread-safe.
** O mutex de impressão garante que mensagens não se misturem.
** Verifica se a simulação ainda está ativa antes de imprimir.
** A mensagem de morte é tratada diretamente pelo monitor sem chamar
** esta função, então aqui sempre verificamos se a simulação está ativa.
*/
void	print_state(t_philo *philo, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!simulation_ended(philo->data))
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

/*
** Verifica de forma segura (com mutex) se a simulação chegou ao fim.
** Retorna 1 se a simulação terminou (morte ou todos saciados), 0 caso contrário.
** Usado por todas as threads para decidir se devem continuar ou parar.
*/
int	simulation_ended(t_data *data)
{
	int	ended;

	pthread_mutex_lock(&data->death_mutex);
	ended = data->simulation_end;
	pthread_mutex_unlock(&data->death_mutex);
	return (ended);
}
