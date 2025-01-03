/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:20:40 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/03 18:35:09 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	forks_creation(t_info *g_data)
{
	int	i;

	i = 0;
	while (i < g_data->nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	threads_creation(t_info *g_data, t_philo *philo_data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sync_order);
	while (i < g_data->nb_philo)
	{
		g_data->thread_count += 1;
		if (pthread_create(&philo_data[i++].threads, NULL, &philo, g_data) != 0)
		{
			perror("Failed to create a thread");
			return (2);
		}
	}
	pthread_mutex_unlock(&sync_order);
}
