/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philosopher_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:45:20 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/20 00:06:25 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat_sleep_routine(t_philo *philo)
{
	grab_fork(philo);
	grab_fork(philo);
	write_status(philo, 0, "is eating");
	sem_wait(philo->sem_meal);
	philo->last_meal = get_time_ms();
	sem_post(philo->sem_meal);
	philo_sleep(philo->table->time_to_eat);
	write_status(philo, 0, "is sleeping");
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
	sem_wait(philo->sem_meal);
	philo->num_forks_held -= 2;
	philo->meals_eaten += 1;
	sem_post(philo->sem_meal);
	philo_sleep(philo->table->time_to_sleep);
}

static void	think_routine(t_philo *philo, int silent)
{
	time_t	time_to_think;

	sem_wait(philo->sem_meal);
	time_to_think = (philo->table->time_to_die
			- (get_time_ms() - philo->last_meal)
			- philo->table->time_to_eat) / 2;
	sem_post(philo->sem_meal);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == 0)
		write_status(philo, 0, "is thinking");
	philo_sleep(time_to_think);
}

static void	lone_philo_routine(t_philo *philo)
{
	philo->sem_philo_full = sem_open(SEM_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, philo->table->num_philos);
	if (philo->sem_philo_full == SEM_FAILED)
		exit(EXIT_ERR_SEM);
	sem_wait(philo->sem_philo_full);
	sync_start(philo->table->start_time);
	if (philo->table->must_eat_cnt == 0)
	{
		sem_post(philo->sem_philo_full);
		exit(EXIT_PHILO_FULL);
	}
	print_status(philo, "has taken a fork");
	philo_sleep(philo->table->time_to_die);
	print_status(philo, "died");
	free_table(philo->table);
	exit(EXIT_PHILO_DEAD);
}

static void	philosopher_routine(t_philo *philo)
{
	if (philo->id % 2)
		think_routine(philo, 1);
	while (1)
	{
		eat_sleep_routine(philo);
		think_routine(philo, 0);
	}
}

void	philosopher(t_table *table)
{
	t_philo	*philo;

	philo = table->this_philo;
	if (philo->table->num_philos == 1)
		lone_philo_routine(philo);
	init_philo_ipc(table, philo);
	if (philo->table->must_eat_cnt == 0)
	{
		sem_post(philo->sem_philo_full);
		child_exit(table, EXIT_PHILO_FULL);
	}
	if (philo->table->time_to_die == 0)
	{
		sem_post(philo->sem_philo_dead);
		child_exit(table, EXIT_PHILO_DEAD);
	}
	sem_wait(philo->sem_meal);
	philo->last_meal = philo->table->start_time;
	sem_post(philo->sem_meal);
	sync_start(philo->table->start_time);
	philosopher_routine(philo);
}
