/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:39:27 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/22 16:55:22 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	delete_threads(t_info *g_data, t_philo *philo_data)
{
	int	i;

	i = 0;
	while (i < g_data->nb_philo)
	{
		if ((pthread_join(philo_data[i++].threads, NULL) != 0))
		{
			perror("Failed to join all threads");
			return (1);
		}
	}
	return (0);
}

void	delete_mutexes(t_info *g_data)
{
	int	i;

	i = 0;
    pthread_mutex_destroy(&g_data->sync_order);
	pthread_mutex_destroy(&g_data->writing);
	pthread_mutex_destroy(&g_data->total_ended_th);
	pthread_mutex_destroy(&g_data->check_dead);
	pthread_mutex_destroy(&g_data->check_increment);
	while (i < g_data->nb_philo)
	{
		pthread_mutex_destroy(&g_data->forks[i]);
		pthread_mutex_destroy(&g_data->all_time_passed[i]);
		i++;
	}
}

void	del_and_free(t_info *g_data, t_philo *philo_data, int part)
{
	// tant que tt les forks sont pas libres on att
	printf("dans del et free\n");
	if (part == 1)
	{
		delete_threads(g_data, philo_data);
		delete_mutexes(g_data);
		free(g_data->forks);
		free(g_data->forks_status);
		free(g_data->time_passed);
	}
	else if (part == 2)
	{
		printf("test1\n");
		delete_mutexes(g_data);
		printf("test2\n");
		free(g_data->forks);
		free(g_data->forks_status);
		free(g_data->time_passed);
	}
}
