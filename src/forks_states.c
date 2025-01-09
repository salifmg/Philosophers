/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:34:00 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/09 19:26:39 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	taking_forks(t_info *g_data, int thread_num)
{
	if (g_data->thread_dead == 1)
        return (1);

	if (g_data->nb_philo == 1) // take single fork
    {
        pthread_mutex_lock(&g_data->forks[thread_num]);
        print_logs(g_data->thread_count, g_data->start_time, "has taken a fork");
        while (g_data->thread_dead == 0)
            usleep(50);
        pthread_mutex_unlock(&g_data->forks[thread_num]);
        return (1);
    }

	while (g_data->forks_status[(thread_num + 1) % g_data->nb_philo] == 1)
	{
		usleep(50);
		if (g_data->thread_dead == 1)
			return (1);
	}
	pthread_mutex_lock(&g_data->forks[(thread_num + 1) % g_data->nb_philo]);
	g_data->forks_status[(thread_num + 1) % g_data->nb_philo] = 1;
	print_logs(g_data->thread_count, g_data->start_time, "has taken a fork");
	if (g_data->thread_dead == 1)
    {
		pthread_mutex_unlock(&g_data->forks[(thread_num + 1) % g_data->nb_philo]);
		g_data->forks_status[(thread_num + 1) % g_data->nb_philo] = 0;
		return (1);
	}
	while (g_data->forks_status[thread_num] == 1)
	{
		usleep(50);
		if (g_data->thread_dead == 1)
		{
			pthread_mutex_unlock(&g_data->forks[(thread_num + 1) % g_data->nb_philo]);
			g_data->forks_status[(thread_num + 1) % g_data->nb_philo] = 0;
		}
		return (1);
	}
	pthread_mutex_lock(&g_data->forks[thread_num]);
	g_data->forks_status[thread_num] = 1;
	print_logs(g_data->thread_count, g_data->start_time, "has taken a fork");
	if (g_data->thread_dead == 1)
		return (leaving_forks(g_data, thread_num));
	return (0);
}

int	leaving_forks(t_info *g_data, int thread_num)
{
	if (g_data->forks_status[(thread_num + 1) % g_data->nb_philo] == 1)
	{
		pthread_mutex_unlock(&g_data->forks[(thread_num + 1) % g_data->nb_philo]);
		g_data->forks_status[(thread_num + 1) % g_data->nb_philo] = 0;
	}
	if (g_data->forks_status[thread_num] == 1)
	{
		pthread_mutex_unlock(&g_data->forks[thread_num]);
		g_data->forks_status[thread_num] = 0;
	}
	if (g_data->thread_dead == 1)
		return (1);
	return (0);
}
