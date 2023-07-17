/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:49:51 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/17 20:42:48 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_strlen(char *s)
{
	long	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	ft_max_l(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

long	get_time_ms(void)
{
	struct timeval	time;
	long			time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000;
	time_ms += time.tv_usec / 1000;
	return (time_ms);
}

void	unlink_global_sems(void)
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
		if (!still_alive(philo->table))
			break ;
		usleep(100);
	}
}
