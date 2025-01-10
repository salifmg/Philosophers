/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:39:27 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/10 19:21:23 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	del_and_free(t_info *g_data, t_philo *philo_data, int part)
{
	if (part == 1)
	{
		delete_threads(g_data, philo_data);
		delete_mutexes(g_data);
		free(g_data->forks);
		free(g_data->forks_status);
	}
	else if (part == 2)
	{
		delete_mutexes(g_data);
		free(g_data->forks);
		free(g_data->forks_status);
	}
}

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
	pthread_mutex_destroy(&g_data->sync_order);
	pthread_mutex_destroy(&g_data->writing);
	while (i < g_data->nb_philo)
	{
		pthread_mutex_destroy(&g_data->forks[i]);
		i++;
	}
}
