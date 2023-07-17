/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse_args_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:49:09 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/17 20:42:30 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

static long	ft_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

static long	philo_atol(char *str)
{
	long	i;
	long	n;

	i = 0;
	n = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == '\n' || str[i] == ' ')
		i++;
	if (str[i] != '\0' && str[i] == '-')
		return (error_msg(NULL, "Error: Invalid argument,\
		 negative number\n", -1));
	if (str[i] != '\0' && str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + str[i] - '0';
		if (n > MAX_PHILOSOPHERS)
			return (error_msg(NULL, "Error: Invalid argument,\
			 number too big\n", -1));
		i++;
	}
	if (str[i] != '\0' || (i && !ft_isdigit(str[i - 1])))
		error_msg(NULL, "Error: Invalid argument, not a number\n", -1);
	return (n);
}

void	parse_args(int argc, char **argv, t_table *table)
{
	table->num_philos = philo_atol(argv[1]);
	table->time_to_die = philo_atol(argv[2]);
	table->time_to_eat = philo_atol(argv[3]);
	table->time_to_sleep = philo_atol(argv[4]);
	if (argc == 6)
		table->must_eat_cnt = philo_atol(argv[5]);
	else
		table->must_eat_cnt = -1;
}

int	valid_args(int argc, char **argv)
{
	long	ans;
	int		i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (error_msg(NULL, "Error: Invalid number of arguments\n", 0));
	while (i < argc)
	{
		ans = philo_atol(argv[i]);
		if (i == 1 && (ans == 0 || ans > MAX_PHILOSOPHERS))
			return (error_msg(NULL, "Error:\
			Invalid number of philosophers\n", 0));
		if (ans < 0)
			return (0);
		i++;
	}
	return (1);
}
