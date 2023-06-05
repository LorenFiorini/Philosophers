/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:19:47 by lfiorini          #+#    #+#             */
/*   Updated: 2023/06/05 04:23:47 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	long	i;

	if (!table)
		return ;
	if (table->fork_locks)
		free(table->fork_locks);
	if (table->philos)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (table->philos[i])
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
}

void	destroy_mutexes(t_table *table)
{
	long	i;

	if (!table)
		return ;
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->stop_sim_lock);
}

int	error_msg(t_table *table, char *str, int ret)
{
	free_table(table);
	write(2, str, ft_strlen(str));
	return (ret);
}
