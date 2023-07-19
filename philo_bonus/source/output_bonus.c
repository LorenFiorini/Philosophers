/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:46:44 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/20 00:52:35 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	msg(char *str, char *detail)
{
	if (!detail)
		printf(str);
	else
		printf(str, detail);
}

int	error_msg(t_table *table, char *str, int ret)
{
	free_table(table);
	write(2, str, ft_strlen(str));
	return (ret);
}

void	write_status(t_philo *philo, int death_report, char *status)
{
	sem_wait(philo->sem_write);
	printf("%ld %ld %s\n", get_time_ms() - philo->table->start_time,
		philo->id + 1, status);
		if (!death_report)
	sem_post(philo->sem_write);
}
