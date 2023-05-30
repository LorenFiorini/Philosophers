/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:22:01 by lfiorini          #+#    #+#             */
/*   Updated: 2023/05/30 05:45:40 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*parse_args(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
		raise_error("Wrong number of arguments", NULL);
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->num_eat = ft_atoi(argv[5]);
	else
		table->num_eat = -1;
	return (table);
}
