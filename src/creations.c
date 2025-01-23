/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:20:40 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/23 16:19:26 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	forks_creation(t_info *g_data)
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
	return (0);
}

int	threads_creation(t_info *g_data, t_philo *philo_data)
{
	int		i;

	i = 0;
	g_data->start_time = get_ctime();
	while (i < g_data->nb_philo)
	{
		while (1)
		{
			pthread_mutex_lock(&g_data->sync_order);
			if (g_data->th_nbr_passed != i)
				pthread_mutex_unlock(&g_data->sync_order);
			else
			{
				pthread_mutex_unlock(&g_data->sync_order);
				break ;
			}
			usleep(100);
		}
		g_data->thread_count = i;
		// printf("thread_count: %d\n", g_data->thread_count); //test
		if (pthread_create(&philo_data[i].threads, NULL, &philo, g_data) != 0)
			return (perror("Failed to create a thread"), 1);
		i++;
	}
	return (0);
}

int	single_thread(t_info *g_data, t_philo *philo_data)
{
	int	i;

	i = 0;
	g_data->start_time = get_ctime();
	while (i < g_data->nb_philo)
	{
		while (1)
		{
			pthread_mutex_lock(&g_data->sync_order);
			if (g_data->th_nbr_passed != i)
				pthread_mutex_unlock(&g_data->sync_order);
			else
			{
				pthread_mutex_unlock(&g_data->sync_order);
				break ;
			}
			usleep(100);
		}
		g_data->thread_count = i;
		if (pthread_create(&philo_data[i].threads, NULL, &philo, g_data) != 0)
			return (perror("Failed to create a thread"), 1);
		if (pthread_detach(philo_data[i++].threads) != 0)
			return (perror("Failed to detach thread"), 1);
	}
	return (0);
}

int	next_fork_index(t_info *g_data, int th_nbr)
{
	return ((th_nbr + 1) % g_data->nb_philo);
}

void	ft_usleep(long ms)
{
	long	begin;

	begin = get_ctime();
	while (get_ctime() - begin > ms)
		usleep(10);
}
