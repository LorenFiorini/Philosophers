/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_grim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 06:54:04 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/08 01:07:19 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_sim_stop_flag(t_table *table, int state)
{
	pthread_mutex_lock(&table->stop_sim_lock);
	table->stop_sim = (long) state;
	pthread_mutex_unlock(&table->stop_sim_lock);
}

static int kill_philo(t_philo *philo)
{
	long	time;

	time = get_time_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		set_sim_stop_flag(philo->table, 1);
		write_status(philo, 1, "died");
		return (1);
	}
	return (0);
}

static int	end_condition_reached(t_table *table)
{
	long	i;
	long	all_ate_enough;

	i = 0;
	all_ate_enough = 1;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
		if (kill_philo(table->philos[i]))
		{
			pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
			return (1);
		}
		if (table->philos[i]->meals_eaten < table->must_eat_cnt)
			all_ate_enough = 0;
		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
		i++;
	}
	if (all_ate_enough && table->must_eat_cnt != -1)
	{
		set_sim_stop_flag(table, 1);
		return (1);
	}
	return (0);
}

void	*grim(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	printf("grim reaper started\n");
	if (table->must_eat_cnt == 0)
		return (NULL);
	set_sim_stop_flag(table, 0);
	sync_start(table->start_time);
	while (1)
	{
		if (end_condition_reached(table))
			break ;
		usleep(1000);
	}
	//while (!end_condition_reached(table))
	//	usleep(1000);
	return (NULL);
}
