/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:01:18 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/05 18:55:38 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	still_alive(t_table *table)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&table->stop_sim_lock);
	if (table->stop_sim)
		i = 0;
	pthread_mutex_unlock(&table->stop_sim_lock);
	return (i);
}

void	write_status(t_philo *philo, int report, char *status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (!still_alive(philo->table) && !report)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	printf("%ld %ld %s\n", get_time_ms() - philo->table->start_time,
		philo->id + 1, status);
	pthread_mutex_unlock(&philo->table->write_lock);
}
