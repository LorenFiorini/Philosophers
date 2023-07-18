/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:55:09 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/18 22:22:00 by lfiorini         ###   ########.fr       */
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
		return (error_msg(table, MALLOC_ERROR, 1));
	parse_args(argc, argv, table);
	if (!init(table))
		return (error_msg(table, MALLOC_ERROR, 1));
	if (!start_simulation(table))
		return (1);
	if (stop_simulation(table) == -1)
		return (table_cleanup(table, 1));
	return (table_cleanup(table, 0));
}

static int	start_grim_reaper_threads(t_table *table)
{
	if (pthread_create(&table->gluttony_reaper, NULL,
			&global_gluttony_reaper, table) != 0)
		return (error_msg(table, THREAD_ERROR, 0));
	if (pthread_create(&table->famine_reaper, NULL,
			&global_famine_reaper, table) != 0)
		return (error_msg(table, THREAD_ERROR, 0));
	return (1);
}

static int	get_child_philo(t_table *table, pid_t *pid)
{
	int	philo_exit_code;
	int	exit_code;

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
				table->philos_full_cnt += 1;
				return (1);
			}
		}
	}
	return (0);
}

int	has_simulation_stopped(t_table *table)
{
	int	ret;

	sem_wait(table->sem_stop);
	ret = table->stop_sim;
	sem_post(table->sem_stop);
	return (ret);
}

int	start_simulation(t_table *table)
{
	int		i;
	pid_t	pid;

	table->start_time = get_time_ms() + (table->num_philos * 20);
	i = 0;
	while (i < table->num_philos)
	{
		pid = fork();
		if (pid == -1)
			return (error_msg(table, FORK_ERROR, 1));
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

int stop_simulation(t_table	*table)
{
	long	i;
	int		exit_code;

	sync_start(table->start_time);
	while (!has_simulation_stopped(table))
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