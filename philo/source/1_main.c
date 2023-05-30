/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:55:09 by lfiorini          #+#    #+#             */
/*   Updated: 2023/05/30 07:11:37 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = parse_args(argc, argv);
	int t = sizeof(t_table);
	int l = sizeof(long);
	int i = sizeof(int);
	int ti = sizeof(time_t);
	printf("t_table\t%d\n", t);
	printf("long   \t%d\n", l);
	printf("int    \t%d\n", i);
	printf("time_t \t%d\n", ti);
	return (0);
}
