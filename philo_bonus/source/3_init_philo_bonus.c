/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_init_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:49:19 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/17 20:41:53 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static int	init_global_semaphores(t_table *table)
{

}

int	init(t_table *table)
{
	if (!init_philosophers(table))
		return (0);
	if (!init_global_semaphores(table))
		return (0);
	// if (pthread_mutex_init(&table->write_lock, NULL) != 0
	// 	|| pthread_mutex_init(&table->stop_sim_lock, NULL) != 0)
	// 	return (error_msg(table, "Error: mutex init failed", 0));
	table->start_time = 0;
	table->stop_sim = 0;
	return (1);
}
