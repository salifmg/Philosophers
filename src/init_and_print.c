/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:28:43 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/08 17:26:12 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_lists(t_info *g_data)
{
	int	i;

	i = 0;
	g_data->time_passed = malloc(sizeof(long) * g_data->nb_philo);
	if (!g_data->time_passed)
		return (1);
	while (i < g_data->nb_philo)
	{
		g_data->time_passed[i] = 0;
		i++;
	}
	g_data->start_time = 0;
	g_data->nb_philo = 0;
	g_data->t_die = 0;
	g_data->t_eat = 0;
	g_data->t_sleep = 0;
	g_data->nb_cycles = 0;
    g_data->thread_count = 0;
	g_data->thread_dead = 0;
	return (0);
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

    pthread_mutex_lock(&g_data->writing);
	if (ft_strcmp(order, "died") == 0 && g_data->thread_dead == 0)
	{
		g_data->thread_dead = 1;
		printf("%ld %d %s\n", elapsed_time, g_data->thread_count, order);
	}
    else if (g_data->thread_dead == 0)
        printf("%ld %d %s\n", elapsed_time, g_data->thread_count, order);
    pthread_mutex_unlock(&g_data->writing);
}
