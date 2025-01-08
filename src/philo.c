/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:27:11 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/08 17:25:59 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eating(t_info *g_data, int thread_num)
{
	long	t_left_eat;
	
	t_left_eat = g_data->t_eat;
	print_logs(g_data, g_data->start_time, "is eating");
	while (t_left_eat && g_data->thread_dead == 0)
	{
		if (9000 < t_left_eat)
		{
			usleep(9000);
			t_left_eat -= 9;
		}
		else
		{
			usleep(t_left_eat * 1000);
			t_left_eat -= t_left_eat;
		}
	}
	if (g_data->thread_dead == 1)
	{
		leaving_forks(g_data, thread_num);
		return (1);
	}
	g_data->time_passed[thread_num] = get_ctime();
	return (0);
}

int	sleeping(t_info *g_data, int thread_num)
{
	long	t_left_sleep;
	
	t_left_sleep = g_data->t_sleep;
	print_logs(g_data, g_data->start_time, "is sleeping");
	while (t_left_sleep && g_data->thread_dead == 0)
	{
		if (9000 < t_left_sleep)
		{
			usleep(9000);
			t_left_sleep -= 9;
		}
		else
		{
			usleep(t_left_sleep * 1000);
			t_left_sleep -= t_left_sleep;
		}
	}
	if (g_data->thread_dead == 1)
	{
		leaving_forks(g_data, thread_num);
		return (1);
	}
	return (0);
}

void *philo(void *param)
{
	long		loop_count;
	t_info		*g_data;
	int			thread_num;

	loop_count = 0;
	g_data = (t_info *)param;
	thread_num = g_data->thread_count - 1;
	pthread_mutex_lock(&g_data->sync_order);
	usleep(5);
	pthread_mutex_unlock(&g_data->sync_order);
	g_data->time_passed[thread_num] = get_ctime();
	while (1)
	{
		taking_forks(g_data, thread_num);
		if (eating(g_data, thread_num) == 1)
			return (1);
		leaving_forks(g_data, thread_num);
		if (sleeping(g_data, thread_num) == 1)
			return (1);
		print_logs(g_data, g_data->start_time, "is thinking"); //delais apres
		if (g_data->nb_cycles && ++loop_count == g_data->nb_cycles)
			break;
	}
	return (0);
}

int philosophers_creation(t_info *g_data, t_philo *philo_data)
{
	pthread_mutex_init(&g_data->sync_order, NULL);
	pthread_mutex_init(&g_data->writing, NULL);
	if (init_lists(g_data) == 1)
		return (1);
	if (forks_creation(g_data) == 1)
		return (1);
	threads_creation(g_data, philo_data);
	check_philos(g_data, 0);
	delete_threads(g_data, philo_data);
	delete_mutexes(g_data);
	free(g_data->forks);
	free(g_data->forks_status);
	return (0);
}
