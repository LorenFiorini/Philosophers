/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:55:09 by lfiorini          #+#    #+#             */
/*   Updated: 2023/05/30 02:00:13 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (1);
	philo = init_philo(argc, argv);
	if (!philo)
		return (1);
	if (philo->error)
	{
		free(philo);
		return (1);
	}
	
	return (0);
}
