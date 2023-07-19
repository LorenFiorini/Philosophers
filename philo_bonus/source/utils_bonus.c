/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:49:51 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/20 00:43:30 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_strcat(char	*dst, char *src)
{
	long	i;
	long	j;

	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

char	*ft_to_string(long n, long digit_count)
{
	char	*str;
	long	i;

	str = malloc(sizeof * str * (digit_count + 1));
	if (str == NULL)
		return (NULL);
	i = digit_count - 1;
	while (i >= 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	str[digit_count] = '\0';
	return (str);
}

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
		if (!still_alive(philo->table))
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
