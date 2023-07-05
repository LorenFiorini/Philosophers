/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philosopher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 04:04:26 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/05 17:35:55 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think_routine(t_philo *philo, long show)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->table->time_to_die
			- (get_time_in_ms() - philo->last_meal)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	time_to_think = ft_max_l(time_to_think, show);
	//if (time_to_think > 600)
	//	time_to_think = 200;
	if (show)
		write_status(philo, 0, "is thinking");
	philo_sleep(philo->table, time_to_think);
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
		return (solo_routine(philo));
	else if (philo->id % 2)
		think_routine(philo, 0);
	while (still_alive(philo->table))
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo, 1);
	}
	return (NULL);
}
