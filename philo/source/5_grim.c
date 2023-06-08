/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_grim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 06:54:04 by lfiorini          #+#    #+#             */
/*   Updated: 2023/06/08 07:03:48 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*grim(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->must_eat_cnt == 0)
		return (NULL);
	while (1)
	{
		if (1)
			break ;
		usleep(1000);
	}
	return (NULL);
}
