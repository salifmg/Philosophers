/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deaths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:45:10 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/20 17:29:17 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_death(t_info *g_data, long last_meal_time, int th_nbr)
{
	long	now;
	long	elapsed_time;

	now = get_ctime();
	elapsed_time = now - g_data->start_time;
	if (now - last_meal_time >= g_data->t_die)
	{
		print_logs(g_data, th_nbr, elapsed_time, "died");
		return (1);
	}
	pthread_mutex_lock(&g_data->check_dead);
	if (g_data->thread_dead == 1)
	{
		pthread_mutex_unlock(&g_data->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&g_data->check_dead);
	return (0);
}

int	check_philos(t_info *g_data)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&g_data->total_ended_th);
		if (g_data->th_end == g_data->nb_philo)
		{
			pthread_mutex_unlock(&g_data->total_ended_th);
			return (0);
		}
		pthread_mutex_unlock(&g_data->total_ended_th);
		pthread_mutex_lock(&g_data->all_time_passed[i]);
		if (check_death(g_data, g_data->time_passed[i], i) == 1)
			break ;
		pthread_mutex_unlock(&g_data->all_time_passed[i]);
		if (++i == g_data->nb_philo)
			i = 0;
		usleep(50); //plus gros ou ptit
	}
	usleep(10000); //plus gros ou ptit
	return (1);
}
