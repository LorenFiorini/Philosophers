/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:49:47 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/17 20:42:42 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_table(t_table *table)
{
	long	i;

	if (!table)
		return ;
	if (table->fork_locks)
		free(table->fork_locks);
	if (table->philos)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (table->philos[i])
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
}

int	error_msg(t_table *table, char *str, int ret)
{
	free_table(table);
	write(2, str, ft_strlen(str));
	return (ret);
}
