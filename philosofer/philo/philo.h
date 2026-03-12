

#ifndef PHILO_H
# define PHILO_H

/*
** Bibliotecas necessárias para threads, mutexes, I/O e operações de tempo.
*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/*
** Constantes de erro e mensagens de estado dos filósofos.
** Cada mensagem segue o formato: timestamp philosopher_id mensagem
*/
# define ERR_ARGS    "Error: invalid arguments\n"
# define ERR_ALLOC   "Error: memory allocation failed\n"
# define ERR_THREAD  "Error: thread creation failed\n"
# define ERR_MUTEX   "Error: mutex initialization failed\n"

# define MSG_FORK    "has taken a fork"
# define MSG_EAT     "is eating"
# define MSG_SLEEP   "is sleeping"
# define MSG_THINK   "is thinking"
# define MSG_DIED    "died"

/*
** Numero minimo e maximo de filosofos permitidos.
*/
# define MIN_PHILOS  1
# define MAX_PHILOS  200

/*
** Estrutura principal que armazena todas as configurações da simulação.
** Compartilhada entre todos os filósofos e a thread monitora.
*/
typedef struct s_data
{
	int				nb_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_must_eat;
	long long		start_time;
	int				simulation_end;
	int				nb_full;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}	t_data;

/*
** Estrutura de cada filósofo.
** Cada filósofo possui seu próprio ID, número de refeições,
** tempo da última refeição e referência ao dado compartilhado.
*/
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

/*
** ============================================================
** Protótipos de funções organizadas por arquivo de origem.
** ============================================================
*/

/* parsing.c - Validação e parse dos argumentos */
int			parse_args(int argc, char **argv, t_data *data);
int			is_valid_number(char *str);

/* utils.c - Funções utilitárias gerais */
int			ft_strlen(const char *str);
long long	ft_atoll(char *str);
long long	get_time(void);
void		ft_sleep(long long duration, t_data *data);
void		print_state(t_philo *philo, char *msg);
int			simulation_ended(t_data *data);

/* init.c - Inicialização de structs e mutexes */
int			init_data(t_data *data);
int			init_philos(t_data *data);
int			init_forks(t_data *data);

/* simulation.c - Criação e gerenciamento das threads */
int			start_simulation(t_data *data);
int			join_threads(t_data *data);

/* routine.c - Rotina principal de cada filósofo */
void		*philo_routine(void *arg);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

/* monitor.c - Thread monitora: verifica mortes e refeições */
void		*monitor_routine(void *arg);
int			check_death(t_data *data);
int			check_all_ate(t_data *data);

/* free.c - Liberação de memória e destruição de mutexes */
void		free_data(t_data *data);
void		destroy_mutexes(t_data *data);

#endif
