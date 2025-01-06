/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:34:00 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/06 17:45:10 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	taking_forks(t_info *g_data, int thread_num, t_timeval current_time)
{
	pthread_mutex_lock(&forks[(thread_num + 1) % g_data->nb_philo]);
	g_data->forks_status[(thread_num + 1) % g_data->nb_philo] = 1; // LE CREER | 0 existe | 1 pris
	print_logs(g_data->thread_count, current_time, " has taken a fork");

	pthread_mutex_lock(&forks[thread_num]);
	g_data->forks_status[thread_num] = 1;
	print_logs(g_data->thread_count, current_time, " has taken a fork");
}

void	leaving_forks(t_info *g_data, int thread_num)
{
	if (g_data->forks_status[(thread_num + 1) % g_data->nb_philo] == 1)
	{
		pthread_mutex_unlock(&forks[(thread_num + 1) % g_data->nb_philo]);
		g_data->forks_status[(thread_num + 1) % g_data->nb_philo] = 0;
	}
	if (g_data->forks_status[thread_num] == 1)
	{
		pthread_mutex_unlock(&forks[thread_num]);
		g_data->forks_status[thread_num] = 0;
	}
}
