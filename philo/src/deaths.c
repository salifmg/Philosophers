/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deaths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:45:10 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/28 20:29:19 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	all_philos_ended(t_info *g_data)
{
	while (1)
	{
		pthread_mutex_lock(&g_data->total_ended_th);
		if (g_data->th_end != g_data->nb_philo)
		{
			pthread_mutex_unlock(&g_data->total_ended_th);
			usleep(100);
		}
		else
		{
			pthread_mutex_unlock(&g_data->total_ended_th);
			break ;
		}
	}
}

int	check_death(t_info *g_data, long last_meal_time, int th_nbr)
{
	long	now;
	long	time_passed;

	now = get_ctime();
	time_passed = now - g_data->start_time;
	if (g_data->t_sleep < g_data->t_die || g_data->t_sleep < g_data->t_eat)
		time_passed -= last_meal_time;
	pthread_mutex_lock(&g_data->total_ended_th);
	if ((time_passed >= g_data->t_die) && (g_data->th_end != g_data->nb_philo))
	{
		print_logs(g_data, th_nbr, g_data->start_time, "died");
		pthread_mutex_unlock(&g_data->total_ended_th);
		return (1);
	}
	pthread_mutex_unlock(&g_data->total_ended_th);
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
		pthread_mutex_lock(&g_data->all_time_passed[i]);
		if (check_death(g_data, g_data->time_passed[i], i) == 1)
		{
			pthread_mutex_unlock(&g_data->all_time_passed[i]);
			break ;
		}
		pthread_mutex_unlock(&g_data->all_time_passed[i]);
		pthread_mutex_lock(&g_data->total_ended_th);
		if (g_data->th_end == g_data->nb_philo)
		{
			pthread_mutex_unlock(&g_data->total_ended_th);
			return (0);
		}
		pthread_mutex_unlock(&g_data->total_ended_th);
		if (++i == g_data->nb_philo)
			i = 0;
		usleep(10);
	}
	return (all_philos_ended(g_data), 1);
}
