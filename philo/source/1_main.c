/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:55:09 by lfiorini          #+#    #+#             */
/*   Updated: 2023/06/05 04:24:54 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start(t_table *table);
static void	stop(t_table *table);

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!valid_args(argc, argv))
		return (error_msg(NULL, STR_USAGE, 1));
	table = malloc(sizeof(t_table));
	if (!table)
		return (error_msg(table, "Error: Malloc failed\n", 1));
	parse_args(argc, argv, table);
	if (!init(table))
		return (error_msg(table, "Error: Malloc failed\n", 1));
	if (!start(table))
		return (1);
	stop(table);
	return (0);
}

static int	start(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				&philosopher, &table->philos[i]) != 0)
			return (error_msg(table, "Error: Thread creation failed\n", 0));
		i++;
	}
	if (table->num_philos > 1)
	{
		if (pthread_create(&table->grim_reaper, NULL,
				&grim_reaper, table) != 0)
			return (error_msg(table, "Error: Thread creation failed\n", 0));
	}
	return (1);
}

static void	stop(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	if (table->num_philos > 1)
		pthread_join(table->grim_reaper, NULL);
	destroy_mutexes(table);
	free_table(table);
}
