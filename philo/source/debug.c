/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:23:20 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/08 01:30:14 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	show_table(t_table *table, int show_philos)
{
	int	i;

	i = 0;
	printf("Table:\n");
	printf("  num_philos: %ld\n", table->num_philos);
	printf("  time_to_die: %ld\n", table->time_to_die);
	printf("  time_to_eat: %ld\n", table->time_to_eat);
	printf("  time_to_sleep: %ld\n", table->time_to_sleep);
	printf("  must_eat_cnt: %ld\n", table->must_eat_cnt);
	printf("  start_time: %ld\n", table->start_time);
	printf("  stop_sim: %ld\n", table->stop_sim);
	printf("  write_lock: %p\n", &table->write_lock);
	printf("  stop_sim_lock: %p\n", &table->stop_sim_lock);
	printf("  philos:\n");
	while (show_philos && i < table->num_philos)
	{
		show_philo(table->philos[i]);
		i++;
	}
}

void	show_philo(t_philo *philo)
{
	printf("    Philo: %ld\n", philo->id);
	printf("      meals_eaten: %ld\n", philo->meals_eaten);
	printf("      left_fork: %ld\n", philo->fork[0]);
	printf("      right_fork: %ld\n", philo->fork[1]);
	printf("      last_meal: %ld\n", philo->last_meal);
	printf("\n");
}
