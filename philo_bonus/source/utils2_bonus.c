/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 22:21:45 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/20 22:22:40 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	has_simulation_stopped(t_table *table)
{
	int	ret;

	sem_wait(table->sem_stop);
	ret = table->stop_sim;
	sem_post(table->sem_stop);
	return (ret);
}

void	unlink_global_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FULL);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_STOP);
}

void	sync_start(long start_time)
{
	while (get_time_ms() < start_time)
		continue ;
}

void	philo_sleep(t_philo *philo, long sleep_time)
{
	long	wake_up;

	wake_up = get_time_ms() + sleep_time;
	while (get_time_ms() < wake_up)
	{
		if (has_simulation_stopped(philo->table))
			break ;
		usleep(100);
	}
}

void	grab_fork(t_philo *philo)
{
	sem_wait(philo->sem_forks);
	sem_wait(philo->sem_meal);
	if (philo->num_forks_held <= 0)
		write_status(philo, 0, "has taken a fork");
	if (philo->num_forks_held == 1)
		write_status(philo, 0, "has taken a fork");
	philo->num_forks_held += 1;
	sem_post(philo->sem_meal);
}
