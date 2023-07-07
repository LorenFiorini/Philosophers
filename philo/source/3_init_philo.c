/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_init_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 03:06:17 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/07 23:34:10 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->num_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->num_philos;
		philo->fork[1] = philo->id;
	}
}

static int	init_philosophers(t_table *table)
{
	long	i;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (error_msg(table, "Error: malloc failed", 0));
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i] = malloc(sizeof(t_philo) * 1);
		if (!table->philos[i])
			return (error_msg(table, "Error: malloc failed", 0));
		if (pthread_mutex_init(&table->philos[i]->meal_time_lock, NULL) != 0)
			return (error_msg(table, "Error: mutex init failed", 0));
		table->philos[i]->id = i;
		table->philos[i]->meals_eaten = 0;
		table->philos[i]->table = table;
		assign_forks(table->philos[i]);
		i++;
	}
	return (1);
}

static int	init_forks(t_table *table)
{
	long	i;

	table->fork_locks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->fork_locks)
		return (error_msg(table, "Error: malloc failed", 0));
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->fork_locks[i], NULL) != 0)
			return (error_msg(table, "Error: mutex init failed", 0));
		i++;
	}
	return (1);
}

int	init(t_table *table)
{
	if (!init_philosophers(table))
		return (0);
	if (!init_forks(table))
		return (0);
	if (pthread_mutex_init(&table->write_lock, NULL) != 0
		|| pthread_mutex_init(&table->stop_sim_lock, NULL) != 0)
		return (error_msg(table, "Error: mutex init failed", 0));
	table->start_time = 0;
	table->stop_sim = 0;
	return (1);
}
