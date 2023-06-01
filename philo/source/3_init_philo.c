/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_init_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 03:06:17 by lfiorini          #+#    #+#             */
/*   Updated: 2023/06/01 04:05:31 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philosophers(t_table *table)
{
	long	i;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!philos)
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
		table->philos[i]->meals = 0;
		table->philos[i]->table = table;
		table->philos[i]->fork[0] = i;
		table->philos[i]->fork[1] = (i + 1) % table->num_philos;

		i++;
	}
	return (1);
}

int	init(t_table *table)
{
	if (!init_philosophers(table))
		return (0);
	
	return (1);
}
