/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_death_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:28:09 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/20 17:46:38 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	end_condition_reached(t_table *table, t_philo *philo)
{
	sem_wait(philo->sem_meal);
	if (get_time_ms() - philo->last_meal >= table->time_to_die)
	{
		write_status(philo, 1, "died");
		sem_post(philo->sem_meal);
		sem_post(table->this_philo->sem_philo_dead);
		return (1);
	}
	if (table->must_eat_cnt != -1 && philo->ate_enough == 0
		&& philo->meals_eaten >= (unsigned int)table->must_eat_cnt)
	{
		sem_post(philo->sem_philo_full);
		philo->ate_enough = 1;
	}
	sem_post(philo->sem_meal);
	return (0);
}

int	kill_all_philos(t_table *table, int ret)
{
	unsigned int	i;

	i = 0;
	while (i < table->num_philos)
	{
		kill(table->pids[i], SIGKILL);
		i++;
	}
	return (ret);
}

void	*global_gluttony_reaper(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->must_eat_cnt < 0 || table->time_to_die == 0
		|| table->num_philos == 1)
		return (NULL);
	sync_start(table->start_time);
	while (table->philos_full_cnt < table->num_philos)
	{
		if (has_simulation_stopped(table) == 1)
			return (NULL);
		sem_wait(table->sem_philo_full);
		if (has_simulation_stopped(table) == 0)
			table->philos_full_cnt += 1;
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

void	*global_famine_reaper(void *data)
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

void	*personal_grim_reaper(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->must_eat_cnt == 0)
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
