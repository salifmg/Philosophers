/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:34:00 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/08 17:27:37 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	taking_forks(t_info *g_data, int thread_num)
{
	pthread_mutex_lock(&g_data->forks[(thread_num + 1) % g_data->nb_philo]);
	g_data->forks_status[(thread_num + 1) % g_data->nb_philo] = 1;
	print_logs(g_data->thread_count, g_data->start_time, " has taken a fork");

	pthread_mutex_lock(&g_data->forks[thread_num]);
	g_data->forks_status[thread_num] = 1;
	print_logs(g_data->thread_count, g_data->start_time, " has taken a fork");
}

void	leaving_forks(t_info *g_data, int thread_num)
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
}
