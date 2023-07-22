/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 22:21:45 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/21 23:34:39 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	grab_fork(t_philo *philo)
{
	sem_wait(philo->sem_forks);
	sem_wait(philo->sem_meal);
	if (philo->num_forks_held <= 0)
		write_status(philo, 0, GOT_FORK_1);
	if (philo->num_forks_held == 1)
		write_status(philo, 0, GOT_FORK_2);
	philo->num_forks_held += 1;
	sem_post(philo->sem_meal);
}

void	*free_table(t_table *table)
{
	long	i;

	if (!table)
		return (NULL);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (table->philos[i] != NULL)
			{
				if (table->philos[i]->sem_meal_name)
					free(table->philos[i]->sem_meal_name);
				free(table->philos[i]);
			}
			i++;
		}
		free(table->philos);
	}
	if (table->pids)
		free(table->pids);
	free(table);
	return (NULL);
}

long	sem_error_cleanup(t_table *table)
{
	sem_close(table->sem_forks);
	sem_close(table->sem_write);
	sem_close(table->sem_philo_full);
	sem_close(table->sem_philo_dead);
	sem_close(table->sem_stop);
	unlink_global_sems();
	return (error_failure(STR_ERR_SEM, NULL, table));
}

long	table_cleanup(t_table *table, long exit_code)
{
	if (table != NULL)
	{
		pthread_join(table->famine_reaper, NULL);
		pthread_join(table->gluttony_reaper, NULL);
		sem_close(table->sem_forks);
		sem_close(table->sem_write);
		sem_close(table->sem_philo_full);
		sem_close(table->sem_philo_dead);
		sem_close(table->sem_stop);
		unlink_global_sems();
		free_table(table);
	}
	return (exit_code);
}
