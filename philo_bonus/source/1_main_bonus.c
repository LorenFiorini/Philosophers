/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:55:09 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/22 23:10:11 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc < 5 || argc > 6)
		return (msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!valid_args(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	if (stop_simulation(table) == -1)
		return (table_cleanup(table, EXIT_FAILURE));
	if (DEBUG_FORMATTING == 1 && table->must_eat_count >= 0)
		write_outcome(table);
	return (table_cleanup(table, EXIT_SUCCESS));
}

long	has_simulation_stopped(t_table *table)
{
	long	ret;

	sem_wait(table->sem_stop);
	ret = table->stop_sim;
	sem_post(table->sem_stop);
	return (ret);
}

long	start_simulation(t_table *table)
{
	long	i;
	pid_t	pid;

	table->start_time = get_time_ms() + (table->num_philos * 20);
	i = -1;
	while (++i < table->num_philos)
	{
		pid = fork();
		if (pid == -1)
			return (error_failure(STR_ERR_FORK, NULL, table));
		else if (pid > 0)
			table->pids[i] = pid;
		else if (pid == 0)
		{
			table->this_philo = table->philos[i];
			philosopher(table);
		}
	}
	if (start_grim_reaper_threads(table) == 0)
		return (0);
	return (1);
}

long	get_child_philo(t_table *table, pid_t *pid)
{
	int		philo_exit_code;
	long	exit_code;

	if (*pid && waitpid(*pid, &philo_exit_code, WNOHANG) != 0)
	{
		if (WIFEXITED(philo_exit_code))
		{
			exit_code = WEXITSTATUS(philo_exit_code);
			if (exit_code == CHILD_EXIT_PHILO_DEAD)
				return (kill_all_philos(table, 1));
			if (exit_code == CHILD_EXIT_ERR_PTHREAD
				|| exit_code == CHILD_EXIT_ERR_SEM)
				return (kill_all_philos(table, -1));
			if (exit_code == CHILD_EXIT_PHILO_FULL)
			{
				table->philo_full_count += 1;
				return (1);
			}
		}
	}
	return (0);
}

long	stop_simulation(t_table	*table)
{
	long	i;
	long	exit_code;

	sync_start(table->start_time);
	while (has_simulation_stopped(table) == 0)
	{
		i = 0;
		while (i < table->num_philos)
		{
			exit_code = get_child_philo(table, &table->pids[i]);
			if (exit_code == 1 || exit_code == -1)
			{
				sem_wait(table->sem_stop);
				table->stop_sim = 1;
				sem_post(table->sem_philo_full);
				sem_post(table->sem_philo_dead);
				sem_post(table->sem_stop);
				return (exit_code);
			}
			i++;
		}
	}
	return (0);
}
