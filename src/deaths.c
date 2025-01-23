/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deaths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:45:10 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/23 18:54:43 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_death(t_info *g_data, long last_meal_time, int th_nbr)
{
	long	now;
	long	time_passed;

	now = get_ctime();
	time_passed = now - g_data->start_time;
	time_passed -= last_meal_time;
	// printf("dans check death\n");

	// printf("%llu\n", time_passed);
	// printf("%ld\n", last_meal_time);
	// printf("%llu\n", (unsigned long long)last_meal_time);
	// printf("%ld\n", now);
	// printf("%ld\n", g_data->start_time);

	pthread_mutex_lock(&g_data->total_ended_th);
	if ((time_passed >= g_data->t_die) && (g_data->th_end != g_data->nb_philo))
	{
		printf("dans check death MORT %ld\n", time_passed);
		print_logs(g_data, th_nbr, g_data->start_time, "died");
		pthread_mutex_unlock(&g_data->total_ended_th);
		return (1);
	}
	pthread_mutex_unlock(&g_data->total_ended_th);
	pthread_mutex_lock(&g_data->check_dead);
	if (g_data->thread_dead == 1)
	{
		// printf("dans check death DEJA\n");
		pthread_mutex_unlock(&g_data->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&g_data->check_dead);
	// printf("dans check death fin\n");
	return (0);
}

int	check_philos(t_info *g_data)
{
	int	i;

	i = 0;
	printf("dans check philo\n");
	while (1)
	{
		pthread_mutex_lock(&g_data->check_increment);
		if (g_data->t_passed_over == g_data->nb_philo)
		{
			pthread_mutex_unlock(&g_data->check_increment);
			break ;
		}
		pthread_mutex_unlock(&g_data->check_increment);
		usleep(500); //plus gros ou ptit probleme jcrois
	}
	while (1)
	{
		// printf("check loop\n");
		//printf("check death appel\n");
		pthread_mutex_lock(&g_data->all_time_passed[i]);
		if (check_death(g_data, g_data->time_passed[i], i) == 1)
		{
			pthread_mutex_unlock(&g_data->all_time_passed[i]);
			printf("check philo break\n");
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
		usleep(50); //plus gros ou ptit
		// printf("check philo looped\n");
	}
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
	printf("check philo FIN\n");
	return (1);
}
