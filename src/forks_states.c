/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:34:00 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/28 20:02:01 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	leaving_taken_fork(t_info *g_data, int th_nbr)
{
	if (g_data->nb_philo == th_nbr + 1)
		return ;
	g_data->forks_status[th_nbr] = 0;
	pthread_mutex_unlock(&g_data->forks[th_nbr]);
}

int	leaving_forks(t_info *g_data, int th_nbr)
{
	if (g_data->forks_status[th_nbr] == 1)
	{
		g_data->forks_status[th_nbr] = 0;
		pthread_mutex_unlock(&g_data->forks[th_nbr]);
	}
	if (g_data->forks_status[next_fork_i(g_data, th_nbr)] == 1)
	{
		g_data->forks_status[next_fork_i(g_data, th_nbr)] = 0;
		pthread_mutex_unlock(&g_data->forks[next_fork_i(g_data, th_nbr)]);
	}
	if (is_philo_dead(g_data, th_nbr, 0) == 1)
		return (1);
	return (0);
}

int	forks_availabity(t_info *g_data, int th_nbr, int part)
{
	if (part == 1)
	{
		while (1)
		{
			pthread_mutex_lock(&g_data->forks[th_nbr]);
			if (g_data->forks_status[th_nbr] == 1)
			{
				pthread_mutex_unlock(&g_data->forks[th_nbr]);
				if (is_philo_dead(g_data, th_nbr, 0) == 1)
					return (1);
				usleep(50);
			}
			else
			{
				pthread_mutex_unlock(&g_data->forks[th_nbr]);
				break ;
			}
		}
	}
	else if (part == 2)
		if (check_second_fork(g_data, th_nbr) == 1)
			return (1);
	return (0);
}

int	taking_forks(t_info *g_data, int th_nbr)
{
	if (is_philo_dead(g_data, th_nbr, 0) == 1)
		return (1);
	if (g_data->nb_philo == 1)
		return (single_fork(g_data, th_nbr));
	if (forks_availabity(g_data, th_nbr, 1) == 1)
		return (1);
	choose_fork(g_data, th_nbr, 1);
	if (is_philo_dead(g_data, th_nbr, 1) == 1)
		return (1);
	if (forks_availabity(g_data, th_nbr, 2) == 1)
		return (1);
	choose_fork(g_data, th_nbr, 2);
	if (is_philo_dead(g_data, th_nbr, 2) == 1)
		return (1);
	return (0);
}

int	single_fork(t_info *g_data, int th_nbr)
{
	print_logs(g_data, th_nbr, g_data->start_time, "has taken a fork");
	while (1)
	{
		pthread_mutex_lock(&g_data->check_dead);
		if (g_data->thread_dead == 1)
		{
			pthread_mutex_unlock(&g_data->check_dead);
			break ;
		}
		pthread_mutex_unlock(&g_data->check_dead);
		usleep(50);
	}
	return (1);
}
