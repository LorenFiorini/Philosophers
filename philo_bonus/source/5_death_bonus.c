/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_death_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:28:09 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/22 18:31:32 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	kill_all_philos(t_table *table, long exit_code)
{
	long	i;

	i = 0;
	while (i < table->num_philos)
	{
		kill(table->pids[i], SIGKILL);
		i++;
	}
	return (exit_code);
}

void	*global_monitor_gluttony(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->must_eat_count < 0 || table->time_to_die == 0
		|| table->num_philos == 1)
		return (NULL);
	sync_start(table->start_time);
	while (table->philo_full_count < table->num_philos)
	{
		if (has_simulation_stopped(table) == 1)
			return (NULL);
		sem_wait(table->sem_philo_full);
		if (has_simulation_stopped(table) == 0)
			table->philo_full_count += 1;
		else
			return (NULL);
	}
	sem_wait(table->sem_stop);
	table->stop_sim = 1;
	kill_all_philos(table, EXIT_SUCCESS);
	sem_post(table->sem_philo_dead);
	sem_post(table->sem_stop);
	return (NULL);
}

void	*global_monitor_famine(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->num_philos == 1)
		return (NULL);
	sync_start(table->start_time);
	if (has_simulation_stopped(table) == 1)
		return (NULL);
	sem_wait(table->sem_philo_dead);
	if (has_simulation_stopped(table) == 1)
		return (NULL);
	sem_wait(table->sem_stop);
	table->stop_sim = 1;
	kill_all_philos(table, EXIT_SUCCESS);
	sem_post(table->sem_philo_full);
	sem_post(table->sem_stop);
	return (NULL);
}

static long	end_condition_reached(t_table *table, t_philo *philo)
{
	sem_wait(philo->sem_meal);
	if (get_time_ms() - philo->last_meal >= table->time_to_die)
	{
		write_status(philo, 1, DIED);
		sem_post(table->this_philo->sem_philo_dead);
		sem_post(philo->sem_meal);
		return (1);
	}
	if (table->must_eat_count != -1 && philo->ate_enough == 0
		&& philo->meals_eaten >= (long)table->must_eat_count)
	{
		sem_post(philo->sem_philo_full);
		philo->ate_enough = 1;
	}
	sem_post(philo->sem_meal);
	return (0);
}

void	*personal_death_monitor(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->must_eat_count == 0)
		return (NULL);
	sem_wait(table->this_philo->sem_philo_dead);
	sem_wait(table->this_philo->sem_philo_full);
	sync_start(table->start_time);
	while (!end_condition_reached(table, table->this_philo))
	{
		usleep(1000);
		continue ;
	}
	return (NULL);
}
