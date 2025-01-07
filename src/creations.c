/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:20:40 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/07 16:00:29 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	forks_creation(t_info *g_data)
{
	int	i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * g_data->nb_philo);
	g_data->forks_status = malloc(sizeof(int) * g_data->nb_philo);
	if (!forks || !g_data->forks_status)
		return (1);
	while (i < g_data->nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		g_data->forks_status[i] = 0;
		i++;
	}
}

void	threads_creation(t_info *g_data, t_philo *philo_data)
{
	int	i;

	i = 0;
	g_data->start_time = get_ctime();
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

long	get_ctime(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void print_logs(t_info *g_data, long start_time, char *order)
{
    long now;
    long elapsed_time;

    now = get_ctime();
    elapsed_time = now - start_time;

    pthread_mutex_lock(&writing);
	if (ft_strcmp(order, "died") == 0 && g_data->thread_dead == 0) // recree la variable
	{
		g_data->thread_dead = 1;
		printf("%ld %d %s\n", elapsed_time, g_data->thread_count, order);
	}
    else if (g_data->thread_dead == 0)
        printf("%ld %d %s\n", elapsed_time, g_data->thread_count, order);
    pthread_mutex_unlock(&writing);
}
