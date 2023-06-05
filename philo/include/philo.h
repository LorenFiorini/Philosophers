/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:54:22 by lfiorini          #+#    #+#             */
/*   Updated: 2023/06/05 03:56:52 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# define MAX_PHILOSOPHERS 255

# define STR_USAGE	"Usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n\
\tnumber_of_philosophers: An integer between 1 and 1024.\n\
\ttime_to_die: An integer between 0 and 2147483647.\n\
\ttime_to_eat: An integer between 0 and 2147483647.\n\
\ttime_to_sleep: An integer between 0 and 2147483647.\n\
\tnumber_of_times_each_philosopher_must_eat: An integer between 0 \
and 2147483647. (Optional)\n"

typedef struct s_philo
{
	pthread_t		thread;
	long			id;
	long			meals;
	long			fork[2];
	long			last_meal;
	pthread_mutex_t	meal_time_lock;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	long			num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat_cnt;
	long			start_time;
	long			stop_sim;
	t_philo			**philos;
	pthread_mutex_t	*fork_locks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	stop_sim_lock;
}	t_table;

// 2_parse_args.c
void	parse_args(int argc, char **argv, t_table *table);
int		valid_args(int argc, char **argv);

// 3_init.c
int		init(t_table *table);

// exits.c
void	free_table(t_table *table);
int		error_msg(t_table *table, char *str, int ret);

// utils.c
int		ft_strlen(char *s);
long	get_time_ms(void);

#endif
