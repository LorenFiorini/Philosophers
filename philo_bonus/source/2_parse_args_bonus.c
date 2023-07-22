/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse_args_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:49:09 by lfiorini          #+#    #+#             */
/*   Updated: 2023/07/22 18:32:32 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static long	contains_only_digits(char *str)
{
	long	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	integer_atoi(char *str)
{
	long	num;
	long	i;

	i = 0;
	num = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
		return (-1);
	return (num);
}

long	valid_args(long argc, char **argv)
{
	long	i;
	long	num;

	i = 1;
	while (i < argc)
	{
		if (!contains_only_digits(argv[i]))
			return (msg(STR_ERR_INPUT_DIGIT, argv[i], 0));
		num = integer_atoi(argv[i]);
		if (i == 1 && (num <= 0 || num > MAX_PHILOS))
			return (msg(STR_ERR_INPUT_POFLOW, STR_MAX_PHILOS, 0));
		if (i != 1 && num == -1)
			return (msg(STR_ERR_INPUT_DIGIT, argv[i], 0));
		i++;
	}
	return (1);
}
