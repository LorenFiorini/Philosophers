/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:55:09 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/18 14:04:33 by lfiorini         ###   ########.fr       */
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
		return (error_msg(table, "Error: Malloc failed.", 1));
	parse_args(argc, argv, table);
	if (!init(table))
		return (error_msg(table, "Error: Malloc failed.", 1));
	if (!start_simulation(table))
		return (1);
	if (stop_simulation(table) == -1)
		return (table_cleanup(table, 1));
	return (table_cleanup(table, 0));
}

int	start_simulation(t_table *table)
{
	int		i;
	pid_t	pid;

	table->start_time = get_time_in_ms() + (table->num_philos * 20);
	i = 0;
	while (i < table->num_philos)
	{
		pid = fork();
		if (pid == -1)
			return (error_msg(table, "Error: Could not fork child.", 1));
		else if (pid > 0)
			table->pids[i] = pid;
		else if (pid == 0)
		{
			table->this_philo = table->philos[i];
			philosopher(table);
		}
		i++;
	}
	if (!start_grim_reaper_threads(table))
		return (0);
	return (1);
}
