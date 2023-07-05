/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:01:18 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/05 17:45:48 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	still_alive(t_table *table)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop)
		i = 0;
	pthread_mutex_unlock(&table->sim_stop_lock);
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
	printf("%ld %d %s\n", get_time_ms() - philo->table->start_time,
		philo->id + 1, status);
	pthread_mutex_unlock(&philo->table->write_lock);
}
