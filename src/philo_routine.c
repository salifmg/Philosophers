/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:27:11 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/26 19:48:58 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	time_after_eating(t_info *g_data, int th_nbr)
{
	pthread_mutex_lock(&g_data->all_time_passed[th_nbr]);
	g_data->time_passed[th_nbr] = get_ctime();
	pthread_mutex_unlock(&g_data->all_time_passed[th_nbr]);
}

int	eating(t_info *g_data, int th_nbr)
{
	long	t_left_eat;

	t_left_eat = g_data->t_eat;
	print_logs(g_data, th_nbr, g_data->start_time, "is eating");
	while (t_left_eat)
	{
		if (check_and_unlock(g_data, th_nbr, 2) == 1)
			return (1);
		usleep(1000);
		t_left_eat--;
	}
	if (check_and_unlock(g_data, th_nbr, 2) == 1)
		return (1);
	time_after_eating(g_data, th_nbr);
	return (0);
}

int	sleeping(t_info *g_data, int th_nbr)
{
	long	t_left_sleep;

	t_left_sleep = g_data->t_sleep;
	print_logs(g_data, th_nbr, g_data->start_time, "is sleeping");
	while (t_left_sleep)
	{
		if (check_and_unlock(g_data, th_nbr, 0) == 1)
			return (1);
		usleep(1000);
		t_left_sleep--;
	}
	if (check_and_unlock(g_data, th_nbr, 0) == 1)
		return (1);
	return (0);
}

void	*philo(void *param)
{
	t_info			*g_data;
	long			loop_count;
	int				th_nbr;

	loop_count = 0;
	g_data = (t_info *)param;
	pthread_mutex_lock(&g_data->sync_order);
	g_data->th_nbr_passed += 1;
	th_nbr = g_data->thread_count;
	pthread_mutex_unlock(&g_data->sync_order);
	if ((th_nbr % 2 == 1) && (g_data->nb_philo > 1))
		ft_usleep(g_data->t_eat / 50);
	while (1)
	{
		if ((philo_actions(g_data, th_nbr) == 1)
			|| (g_data->nb_cycles && ++loop_count == g_data->nb_cycles))
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
	return (del_and_free(g_data, philo_data, 1), 0);
}
