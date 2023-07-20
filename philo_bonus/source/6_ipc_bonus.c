/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_ipc_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:35:59 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/20 22:20:54 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_open_global_semaphores(t_philo *philo)
{
	philo->sem_forks = sem_open(SEM_FORKS, O_CREAT,
			S_IRUSR | S_IWUSR, philo->table->num_philos);
	philo->sem_philo_dead = sem_open(SEM_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, philo->table->num_philos);
	philo->sem_philo_full = sem_open(SEM_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, philo->table->num_philos);
	philo->sem_write = sem_open(SEM_WRITE, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (philo->sem_philo_dead == SEM_FAILED
		|| philo->sem_philo_full == SEM_FAILED
		|| philo->sem_forks == SEM_FAILED
		|| philo->sem_write == SEM_FAILED)
		return (0);
	return (1);
}

int	philo_open_local_semaphores(t_philo *philo)
{
	philo->sem_meal = sem_open(philo->sem_meal_name, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (philo->sem_meal == SEM_FAILED)
		return (0);
	sem_unlink(philo->sem_meal_name);
	return (1);
}

void	interprocess_communication(t_table *table, t_philo *philo)
{
	if (table->num_philos == 1)
		return ;
	sem_unlink(philo->sem_meal_name);
	if (philo_open_global_semaphores(philo) == 0)
		child_exit(table, EXIT_ERR_SEM);
	if (philo_open_local_semaphores(philo) == 0)
		child_exit(table, EXIT_ERR_SEM);
	if (pthread_create(&philo->thread, NULL,
			&personal_grim_reaper, table) != 0)
		child_exit(table, EXIT_ERR_PTHREAD);
	return ;
}
