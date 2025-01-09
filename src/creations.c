/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:20:40 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/09 19:18:36 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	forks_creation(t_info *g_data)
{
	int	i;

	i = 0;
	g_data->forks = malloc(sizeof(pthread_mutex_t) * g_data->nb_philo);
	g_data->forks_status = malloc(sizeof(int) * g_data->nb_philo);
	if (!g_data->forks || !g_data->forks_status)
		return (1);
	while (i < g_data->nb_philo)
	{
		pthread_mutex_init(&g_data->forks[i], NULL);
		g_data->forks_status[i] = 0;
		i++;
	}
}

void	threads_creation(t_info *g_data, t_philo *philo_data)
{
	int	i;

	i = 0;
	g_data->start_time = get_ctime();
	while (i < g_data->nb_philo)
	{
		g_data->thread_count += 1;
		if (pthread_create(&philo_data[i].threads, NULL, &philo, g_data) != 0)
			return (perror("Failed to create a thread"), 2);
	}
}

void	single_thread(t_info *g_data, t_philo *philo_data)
{
	int	i;

	i = 0;
	g_data->start_time = get_ctime();
	while (i < g_data->nb_philo)
	{
		g_data->thread_count += 1;
		if (pthread_create(&philo_data[i].threads, NULL, &philo, g_data) != 0)
			return (perror("Failed to create a thread"), 2);
		if (pthread_detach(philo_data[i].threads) != 0)
            return (perror("Failed to detach thread"), 2);
	}
}
