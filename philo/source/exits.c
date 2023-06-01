/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:19:47 by lfiorini          #+#    #+#             */
/*   Updated: 2023/06/01 03:22:32 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	long	i;

	if (!table)
		return ;
	i = 0;
	while (i < table->num_philos)
	{
		free(table->philos[i]);
		i++;
	}
	free(table);
}

int	error_msg(t_table *table, char *str, int ret)
{
	free_table(table);
	write(2, str, ft_strlen(str));
	return (ret);
}
