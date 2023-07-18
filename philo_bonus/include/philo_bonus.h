/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:54:22 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/18 18:00:38 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <semaphore.h>

# ifndef MAX_PHILOSOPHERS
#  define MAX_PHILOSOPHERS 1000
# endif

# define STR_USAGE	"Usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n\
\tnumber_of_philosophers: An integer between 1 and 1024.\n\
\ttime_to_die: An integer between 0 and 2147483647.\n\
\ttime_to_eat: An integer between 0 and 2147483647.\n\
\ttime_to_sleep: An integer between 0 and 2147483647.\n\
\tnumber_of_times_each_philosopher_must_eat: An integer between 0 \
and 2147483647. (Optional)\n"

# define THREAD_ERROR	"Error: Could not create thread.\n"
# define FORK_ERROR		"Error: Could not fork child.\n"
# define SEM_ERROR		"Error: Could not create semaphore.\n"
# define MALLOC_ERROR	"Error: Could not allocate memory.\n"

# define SEM_WRITE	"/philo_global_write"
# define SEM_STOP	"/philo_global_stop"
# define SEM_MEAL	"/philo_local_meal_"
# define SEM_FULL	"/philo_global_full"
# define SEM_FORKS	"/philo_global_forks"
# define SEM_DEAD	"/philo_global_dead"

# define CHILD_EXIT_ERR_PTHREAD	2
# define CHILD_EXIT_ERR_SEM		3
# define CHILD_EXIT_PHILO_FULL	4
# define CHILD_EXIT_PHILO_DEAD	5

typedef struct s_philo	t_philo;

typedef struct s_table
{
	long			num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat_cnt;
	long			start_time;
	long			stop_sim;
	long			philos_full_cnt;
	pid_t			*pids;
	t_philo			**philos;
	t_philo			*this_philo;
	pthread_t		gluttony_reaper;
	pthread_t		famine_reaper;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_philo_full;
	sem_t			*sem_philo_dead;
	sem_t			*sem_stop;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	long			id;
	long			meals_eaten;
	long			num_forks_held;
	long			ate_enough;
	long			last_meal;
	pthread_mutex_t	personal_grim_reaper;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_philo_full;
	sem_t			*sem_philo_dead;
	char			*sem_meal_name;
	sem_t			*sem_meal;
	t_table			*table;
}	t_philo;

// 1_main_bonus.c
int		start_simulation(t_table *table);

// 2_parse_args_bonus.c
void	parse_args(int argc, char **argv, t_table *table);
int		valid_args(int argc, char **argv);

// 3_init_bonus.c
int		init(t_table *table);

// exits_bonus.c
void	free_table(t_table *table);
int		sem_error_cleanup(t_table *table);
int		table_cleanup(t_table *table, int exit_code);
void	destroy_mutexes(t_table *table);
int		error_msg(t_table *table, char *str, int ret);

// status_bonus.c
int		still_alive(t_table *table);
void	write_status(t_philo *philo, int report, char *status);

// utils_bonus.c
long	ft_max_l(long a, long b);
long	get_time_ms(void);
void	sync_start(long start_time);
void	philo_sleep(t_philo *philo, long sleep_time);

#endif
