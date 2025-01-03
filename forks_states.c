/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:34:00 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/03 17:30:38 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	taking_forks(t_info *g_data, int thread_num, t_timeval current_time)
{
	pthread_mutex_lock(&forks[(thread_num + 1) % g_data->nb_philo]);
	fork_status[(thread_num + 1) % g_data->nb_philo] = 1; // LE CREER | 0 existe | 1 pris
	printf("%ld %d has taken a fork", current_time.tv_usec, g_data->thread_count);

	pthread_mutex_lock(&forks[thread_num]);
	fork_status[thread_num] = 1;
	printf("%ld %d has taken a fork", current_time.tv_usec, g_data->thread_count);
}

void	leaving_forks(t_info *g_data, int thread_num, t_timeval current_time)
{
	if (fork_status[(thread_num + 1) % g_data->nb_philo] == 1)
	{
		pthread_mutex_unlock(&forks[(thread_num + 1) % g_data->nb_philo]);
		fork_status[(thread_num + 1) % g_data->nb_philo] = 0;
	}
	if (fork_status[thread_num] == 1)
	{
		pthread_mutex_unlock(&forks[thread_num]);
		fork_status[thread_num] = 0;
	}
}

/* void	forks_status(t_info *g_data)
{
	int	i;

	i = 0;
	while (i < g_data->nb_philo)
	{
		if (fork_status[i] == 1)
			printf("%ld %d has taken a fork", current_time.tv_usec, g_data->thread_count);
		i++;
	}
} */
