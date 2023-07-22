/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:54:22 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/22 18:32:32 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef MAX_PHILOS
#  define MAX_PHILOS	200
# endif
# ifndef DEBUG_FORMATTING
#  define DEBUG_FORMATTING 0
# endif
# define STR_MAX_PHILOS "200"

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# define STR_PROG_NAME	"philo_bonus:"
# define STR_USAGE	"%s usage: ./philo_bonus <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"%s invalid input: %s: \
not a valid longeger between 0 and 2147483647.\n"
# define STR_ERR_INPUT_POFLOW	"%s invalid input: \
there must be between 1 and %s philosophers.\n"
# define STR_ERR_THREAD	"%s error: Could not create thread.\n"
# define STR_ERR_MALLOC	"%s error: Could not allocate memory.\n"
# define STR_ERR_SEM	"%s error: Could not create semaphore.\n"
# define STR_ERR_FORK	"%s error: Could not fork child.\n"

# define SEM_NAME_FORKS "/philo_global_forks"
# define SEM_NAME_WRITE "/philo_global_write"
# define SEM_NAME_FULL	"/philo_global_full"
# define SEM_NAME_DEAD	"/philo_global_dead"
# define SEM_NAME_STOP	"/philo_global_stop"
# define SEM_NAME_MEAL	"/philo_local_meal_"

# define CHILD_EXIT_ERR_PTHREAD	2
# define CHILD_EXIT_ERR_SEM		3
# define CHILD_EXIT_PHILO_FULL	4
# define CHILD_EXIT_PHILO_DEAD	5

typedef struct s_philo	t_philo;

typedef struct s_table
{
	long		num_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		must_eat_count;
	long		start_time;
	long		stop_sim;
	long		philo_full_count;
	pid_t		*pids;
	pthread_t	famine_reaper;
	pthread_t	gluttony_reaper;
	sem_t		*sem_forks;
	sem_t		*sem_philo_dead;
	sem_t		*sem_philo_full;
	sem_t		*sem_stop;
	sem_t		*sem_write;
	t_philo		**philos;
	t_philo		*this_philo;
}	t_table;

typedef struct s_philo
{
	long		id;
	long		meals_eaten;
	long		num_forks_held;
	long		ate_enough;
	long		last_meal;
	char		*sem_meal_name;
	sem_t		*sem_forks;
	sem_t		*sem_meal;
	sem_t		*sem_philo_dead;
	sem_t		*sem_philo_full;
	sem_t		*sem_write;
	t_table		*table;
	pthread_t	personal_death_monitor;
}	t_philo;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

// 1_main_bonus.c
long	has_simulation_stopped(t_table *table);
long	start_simulation(t_table *table);
long	get_child_philo(t_table *table, pid_t *pid);
long	stop_simulation(t_table	*table);

// 2_parse_args_bonus.c
long	valid_args(long argc, char **argv);
long	integer_atoi(char *str);

// 3_init_bonus.c
t_table	*init_table(long argc, char **argv, long i);

// 4_philosopher_bonus.c
void	philosopher(t_table *table);

// 5_death_bonus.c
void	*global_monitor_gluttony(void *data);
void	*global_monitor_famine(void *data);
void	*personal_death_monitor(void *data);
long	kill_all_philos(t_table *table, long exit_code);

// 6_ipc_bonus.c
void	init_philo_ipc(t_table *table, t_philo *philo);

// exits_bonus.c
void	child_exit(t_table *table, long exit_code);
long	msg(char *str, char *detail, long exit_no);
long	error_failure(char *str, char *details, t_table *table);
void	*error_null(char *str, char *details, t_table *table);

// output_bonus.c
void	write_status(t_philo *philo, long reaper, t_status status);
void	print_status(t_philo *philo, char *str);
void	print_status_debug(t_philo *philo, char *color, char *str,
			t_status status);
void	write_outcome(t_table *table);

//	time.c
long	get_time_ms(void);
void	philo_sleep(long sleep_time);
void	sync_start(long start_time);

// utils_bonus.c
char	*ft_ltoa(long num, long len);
char	*ft_strcat(char	*dst, const char *src);
long	ft_strlen(const char *str);
void	unlink_global_sems(void);
long	start_grim_reaper_threads(t_table *table);

// utils2_bonus.c
void	grab_fork(t_philo *philo);
void	*free_table(t_table *table);
long	sem_error_cleanup(t_table *table);
long	table_cleanup(t_table *table, long exit_code);

#endif
