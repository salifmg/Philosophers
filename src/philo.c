/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:27:11 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/12 17:25:47 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	eating(t_info *g_data, int th_nbr)
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
		return (leaving_forks(g_data, th_nbr));
	g_data->time_passed[th_nbr] = get_ctime();
	return (0);
}

int	sleeping(t_info *g_data, int th_nbr)
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
		return (leaving_forks(g_data, th_nbr));
	return (0);
}

void	*philo(void *param)
{
	long		loop_count;
	t_info		*g_data;
	int			th_nbr;

	loop_count = 0;
	g_data = (t_info *)param;
	th_nbr = g_data->thread_count;
	pthread_mutex_lock(&g_data->sync_order);
	usleep(100); //plus gros ou ptit
	pthread_mutex_unlock(&g_data->sync_order);
	g_data->time_passed[th_nbr] = get_ctime();
	while (1)
	{
		if (philo_actions(g_data, th_nbr) == 1)
			break ;
		if (g_data->nb_cycles && ++loop_count == g_data->nb_cycles)
		{
			g_data->th_end += 1;
			break ;
		}
	}
	if (g_data->thread_dead == 1)
		return (1);
	return (0);
}

int	philosophers_creation(t_info *g_data, t_philo *philo_data)
{
	pthread_mutex_init(&g_data->sync_order, NULL);
	pthread_mutex_init(&g_data->writing, NULL);
	if (init_lists(g_data) == 1)
		return (1);
	if (forks_creation(g_data) == 1)
		return (1);
	if (threads_creation(g_data, philo_data) == 1)
	{
		del_and_free(g_data, philo_data, 1);
		return (1);
	}
	if (check_philos(g_data, 0) == 1)
	{
		del_and_free(g_data, philo_data, 1);
		return (1);
	}
	del_and_free(g_data, philo_data, 1);
	return (0);
}

int	single_philosopher(t_info *g_data, t_philo *philo_data)
{
	pthread_mutex_init(&g_data->sync_order, NULL);
	pthread_mutex_init(&g_data->writing, NULL);
	if (init_lists(g_data) == 1)
		return (1);
	if (forks_creation(g_data) == 1)
		return (1);
	if (single_thread(g_data, philo_data) == 1)
	{
		del_and_free(g_data, philo_data, 2);
		return (1);
	}
	if (check_philos(g_data, 0) == 1)
	{
		del_and_free(g_data, philo_data, 2);
		return (1);
	}
	del_and_free(g_data, philo_data, 2);
	return (0);
}
