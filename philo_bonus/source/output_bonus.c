/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:46:44 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/19 22:49:54 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_status(t_philo *philo, int death_report, char *status)
{
	sem_wait(philo->sem_write);
	printf("%ld %ld %s\n", get_time_ms() - philo->table->start_time,
		philo->id + 1, status);
		if (!death_report)
	sem_post(philo->sem_write);
}
