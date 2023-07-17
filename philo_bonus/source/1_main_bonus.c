/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:55:09 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/17 20:41:55 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!valid_args(argc, argv))
		return (error_msg(NULL, STR_USAGE, 1));
	table = malloc(sizeof(t_table));
	if (!table)
		return (error_msg(table, "Error: Malloc failed\n", 1));

	return (0);
}
