/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:22:01 by lfiorini          #+#    #+#             */
/*   Updated: 2023/05/30 07:09:31 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static long	ft_atol(char *str, t_table *table)
{
	long	i;
	long	n;
	long	s;

	i = 0;
	n = 0;
	s = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == '\n' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s = -1;
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + str[i] - '0';
		if (n * s < MIN_INT || n * s > MAX_INT)
			error_exit(table, "Error: Argument out of range\n");
		i++;
	}
	if (str[i] != '\0' || (i && !ft_isdigit(str[i - 1])))
		error_exit(table, "Error: Argument is not a number\n");
	if (n * s < 0)
		error_exit(table, "Error: Argument is negative\n");
	return (n * s);
}

t_table	*parse_args(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
		error_exit(NULL, STR_USAGE);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->num_philos = ft_atol(argv[1], table);
	table->time_to_die = ft_atol(argv[2], table);
	table->time_to_eat = ft_atol(argv[3], table);
	table->time_to_sleep = ft_atol(argv[4], table);
	if (argc == 6)
		table->must_eat_cnt = ft_atol(argv[5], table);
	else
		table->must_eat_cnt = -1;
	return (table);
}
