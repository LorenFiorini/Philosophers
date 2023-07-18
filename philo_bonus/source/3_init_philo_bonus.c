/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_init_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:49:19 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/18 19:58:00 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*set_sem_names(char *str, long id)
{
	long	i;
	long	digit_count;
	char	*sem_name;
	char	*tmp;

	digit_count = 0;
	i = id;
	while (i)
	{
		digit_count++;
		i /= 10;
	}
	i = ft_strlen(str) + digit_count;
	sem_name = malloc (sizeof * sem_name * (i + 1));
	if (sem_name == NULL)
		return (NULL);
	sem_name[0] = '\0';
	sem_name = ft_strcat(sem_name, str);
	tmp = ft_to_string(id, digit_count);
	sem_name = ft_strcat(sem_name, tmp);
	free(tmp);
	return (sem_name);
}

static int	init_philosophers(t_table *table)
{
	long	i;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (error_msg(table, MALLOC_ERROR, 0));
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i] = malloc(sizeof(t_philo) * 1);
		if (!table->philos[i])
			return (error_msg(table, MALLOC_ERROR, 0));
		table->philos[i]->sem_meal_name = set_sem_names(SEM_MEAL, philo->id + 1);
		if (table->philos[i]->sem_meal_name == NULL)
			return (error_msg(table, MALLOC_ERROR, 0));
		table->philos[i]->id = i;
		table->philos[i]->meals_eaten = 0;
		table->philos[i]->num_forks_held = 0;
		table->philos[i]->ate_enough = 0;
		table->philos[i]->table = table;
		i++;
	}
	return (1);
}

static int	init_global_semaphores(t_table *table)
{
	unlink_global_semaphores(table);

	table->sem_forks = sem_open(SEM_FORKS, O_CREAT,
			S_IRUSR | S_IWUSR, table->num_philos);
	table->sem_write = sem_open(SEM_WRITE, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	table->sem_philo_full = sem_open(SEM_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, table->num_philos);
	table->sem_philo_dead = sem_open(SEM_DEAD, O_CREAT,
			S_IRUSR | S_IWUSR, table->num_philos);
	table->sem_stop = sem_open(SEM_STOP, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (table->sem_forks == SEM_FAILED
		|| table->sem_write == SEM_FAILED
		|| table->sem_philo_full == SEM_FAILED
		|| table->sem_philo_dead == SEM_FAILED
		|| table->sem_stop == SEM_FAILED)
		return (sem_error_cleanup(table));
	return (1);
}

int	init(t_table *table)
{
	if (!init_global_semaphores(table))
		return (0);
	if (!init_philosophers(table))
		return (0);
	table->pids = malloc(sizeof(pid_t) * table->num_philos);
	if (!table->pids)
		return (error_msg(table, MALLOC_ERROR, 0));
	table->philos_full_cnt = 0;
	table->start_time = 0;
	table->stop_sim = 0;
	return (1);
}
