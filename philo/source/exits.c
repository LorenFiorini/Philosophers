/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:19:47 by lfiorini          #+#    #+#             */
/*   Updated: 2023/05/30 05:42:20 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	if (!table)
		return ;

	free(table);
}

void	error_exit(t_table *table, char *str)
{
	free_table(table);
	write(2, str, ft_strlen(str));
	exit(1);
}
