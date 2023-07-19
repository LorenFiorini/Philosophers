/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:49:47 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/20 00:54:41 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_table(t_table *table)
{
	long	i;

	if (!table)
		return ;
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (table->philos[i] != NULL)
			{
				if (table->philos[i]->sem_meal)
					free(table->philos[i]->sem_meal);
				free(table->philos[i]);
			}
			i++;
		}
		free(table->philos);
	}
	if (table->pids)
		free(table->pids);
	free(table);
}

int	sem_error_cleanup(t_table *table)
{
	sem_close(table->sem_forks);
	sem_close(table->sem_philo_dead);
	sem_close(table->sem_philo_full);
	sem_close(table->sem_stop);
	sem_close(table->sem_write);
	unlink_global_semaphores();
	return (error_msg(table, "Error: Could not\
	create semaphore.\n", EXIT_FAILURE));
}

int	table_cleanup(t_table *table, int ret)
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
		unlink_global_semaphores();
		free_table(table);
	}
	return (ret);
}

void	child_exit(t_table *table, int exit_code)
{
	sem_post(table->this_philo->sem_meal);
	pthread_join(table->this_philo->personal_grim_reaper, NULL);
	if (exit_code == EXIT_ERR_SEM)
		error_msg(table, SEM_ERROR, 0);
	if (exit_code == EXIT_ERR_PTHREAD)
		error_msg(table, THREAD_ERROR, 0);
	sem_close(table->this_philo->sem_forks);
	sem_close(table->this_philo->sem_meal);
	sem_close(table->this_philo->sem_philo_dead);
	sem_close(table->this_philo->sem_philo_full);
	sem_close(table->this_philo->sem_write);
	free_table(table);
	exit(exit_code);
}
