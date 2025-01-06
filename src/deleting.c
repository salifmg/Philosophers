/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:39:27 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/06 17:45:12 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	delete_threads(t_info *g_data, t_philo *philo_data)
{
	int	i;

	i = 0;
	while (i < g_data->nb_philo)
	{
		if ((pthread_join(philo_data[i++].threads, NULL) != 0))
		{
			perror("Failed to join all threads");
			return (3);
		}
	}
}

void	delete_mutexes(t_info *g_data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&sync_order);
	pthread_mutex_destroy(&writing);
	while (i < g_data->nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
