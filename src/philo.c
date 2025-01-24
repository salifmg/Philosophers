/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:27:11 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/24 20:16:10 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	eating(t_info *g_data, int th_nbr)
{
	long	t_left_eat;

	t_left_eat = g_data->t_eat;
	print_logs(g_data, th_nbr, g_data->start_time, "is eating");
	while (t_left_eat)
	{
		pthread_mutex_lock(&g_data->check_dead);
		if (g_data->thread_dead == 1)
		{
			pthread_mutex_unlock(&g_data->check_dead);
			break ;
		}
		pthread_mutex_unlock(&g_data->check_dead);
		if (10 <= t_left_eat)
		{
			usleep(1000);
			t_left_eat -= 1;
		}
		else if (t_left_eat > 0)
		{
			usleep(t_left_eat * 100);
			t_left_eat -= t_left_eat;
		}
	}
	pthread_mutex_lock(&g_data->check_dead);
	if (g_data->thread_dead == 1)
	{
		pthread_mutex_unlock(&g_data->check_dead);
		return (leaving_forks(g_data, th_nbr));
	}
	pthread_mutex_unlock(&g_data->check_dead);
	pthread_mutex_lock(&g_data->all_time_passed[th_nbr]);
	g_data->time_passed[th_nbr] = get_ctime();
	pthread_mutex_unlock(&g_data->all_time_passed[th_nbr]);
	return (0);
}

int	sleeping(t_info *g_data, int th_nbr)
{
	long	t_left_sleep;

	t_left_sleep = g_data->t_sleep;
	print_logs(g_data, th_nbr, g_data->start_time, "is sleeping");
	while (t_left_sleep)
	{
		pthread_mutex_lock(&g_data->check_dead);
		if (g_data->thread_dead == 1)
		{
			pthread_mutex_unlock(&g_data->check_dead);
			break ;
		}
		pthread_mutex_unlock(&g_data->check_dead);
		if (10 <= t_left_sleep)
		{
			usleep(1000);
			t_left_sleep -= 1;
		}
		else if (t_left_sleep > 0)
		{
			usleep(t_left_sleep * 100);
			t_left_sleep -= t_left_sleep;
		}
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

void	*philo(void *param)
{
	t_info			*g_data;
	long			loop_count;
	int				th_nbr;

	g_data = (t_info *)param;
	pthread_mutex_lock(&g_data->sync_order);
	g_data->th_nbr_passed += 1;
	th_nbr = g_data->thread_count;
	pthread_mutex_unlock(&g_data->sync_order);
	if ((th_nbr % 2  == 1) && (g_data->nb_philo > 1))
		ft_usleep(g_data->t_eat / 50);
	pthread_mutex_lock(&g_data->check_increment);
	g_data->t_passed_over += 1;
	pthread_mutex_unlock(&g_data->check_increment);
	loop_count = 0;
	while (1)
	{
		if ((philo_actions(g_data, th_nbr) == 1) || (g_data->nb_cycles && ++loop_count == g_data->nb_cycles))
			break ;
	}
	pthread_mutex_lock(&g_data->total_ended_th);
	g_data->th_end += 1;
	pthread_mutex_unlock(&g_data->total_ended_th);
	return (0);
}

int	philosophers_creation(t_info *g_data, t_philo *philo_data)
{
	pthread_mutex_init(&g_data->sync_order, NULL);
	pthread_mutex_init(&g_data->writing, NULL);
	pthread_mutex_init(&g_data->total_ended_th, NULL);
	pthread_mutex_init(&g_data->check_dead, NULL);
	pthread_mutex_init(&g_data->check_increment, NULL);
	if (init_lists(g_data) == 1)
		return (1);
	if (forks_creation(g_data) == 1)
		return (1);
	if (threads_creation(g_data, philo_data) == 1)
	{
		if (g_data->nb_philo == 1)
			return (del_and_free(g_data, philo_data, 2), 1);
		return (del_and_free(g_data, philo_data, 1), 1);
	}
	if (check_philos(g_data) == 1)
	{
		if (g_data->nb_philo == 1)
			return (del_and_free(g_data, philo_data, 2), 1);
		return (del_and_free(g_data, philo_data, 1), 1);
	}
	del_and_free(g_data, philo_data, 1);
	return (0);
}
