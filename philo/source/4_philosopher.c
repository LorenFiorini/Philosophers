/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philosopher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 04:04:26 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/11 03:08:58 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo, long show)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->table->time_to_die
			- (get_time_ms() - philo->last_meal)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	time_to_think = ft_max_l(time_to_think, show);
	if (show)
		write_status(philo, 0, "is thinking");
	philo_sleep(philo, time_to_think);
}

static void	eat_and_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, 0, "has taken a fork");
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	write_status(philo, 0, "has taken a fork");
	write_status(philo, 0, "is eating");
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleep(philo, philo->table->time_to_eat);
	if (still_alive(philo->table))
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	write_status(philo, 0, "is sleeping");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	philo_sleep(philo, philo->table->time_to_sleep);
}

static void	*solo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, 0, "has taken a fork");
	philo_sleep(philo, philo->table->time_to_die);
	write_status(philo, 0, "died");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->must_eat_cnt == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sync_start(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->num_philos == 1)
		return (solo(philo));
	else if (philo->id % 2)
		think(philo, 0);
	while (still_alive(philo->table))
	{
		eat_and_sleep(philo);
		think(philo, 1);
	}
	return (NULL);
}
