/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:22:01 by lfiorini          #+#    #+#             */
/*   Updated: 2023/05/30 06:18:05 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(char *str, t_table *table)
{
	int		i;
	long	n;
	int		s;

	i = 0;
	n = 0;
	s = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == '\n' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s = -1;
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		if (n * s < MIN_INT || n * s > MAX_INT)
			error_exit(table, "Error: Argument out of range\n");
		i++;
	}
	if (str[i] != '\0' || (i && !ft_isdigit(str[i - 1])))
		error_exit(table, "Error: Argument is not a number\n");
	return ((int)(n * s));
}

t_table	*parse_args(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
		error_exit(NULL, STR_USAGE);
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->num_philos = ft_atoi(argv[1], table);
	table->time_to_die = ft_atoi(argv[2], table);
	table->time_to_eat = ft_atoi(argv[3], table);
	table->time_to_sleep = ft_atoi(argv[4], table);
	if (argc == 6)
		table->num_eat = ft_atoi(argv[5], table);
	else
		table->num_eat = -1;
	return (table);
}
