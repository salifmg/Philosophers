/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:13:58 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/28 20:01:59 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_second_fork(t_info *g_data, int th_nbr)
{
	while (1)
	{
		pthread_mutex_lock(&g_data->forks[next_fork_i(g_data, th_nbr)]);
		if (g_data->forks_status[next_fork_i(g_data, th_nbr)] == 1)
		{
			pthread_mutex_unlock(&g_data->forks[next_fork_i(g_data, th_nbr)]);
			if (is_philo_dead(g_data, th_nbr, 1) == 1)
				return (1);
			usleep(50);
		}
		else
		{
			pthread_mutex_unlock(&g_data->forks[next_fork_i(g_data, th_nbr)]);
			break ;
		}
	}
	return (0);
}

int	is_philo_dead(t_info *g_data, int th_nbr, int forks_taken)
{
	pthread_mutex_lock(&g_data->check_dead);
	if (g_data->thread_dead == 1)
	{
		if (forks_taken == 0)
		{
			pthread_mutex_unlock(&g_data->check_dead);
			return (1);
		}
		else if (forks_taken == 1)
		{
			leaving_taken_fork(g_data, th_nbr);
			pthread_mutex_unlock(&g_data->check_dead);
			return (1);
		}
		else if (forks_taken == 2)
		{
			pthread_mutex_unlock(&g_data->check_dead);
			return (leaving_forks(g_data, th_nbr));
		}
	}
	pthread_mutex_unlock(&g_data->check_dead);
	return (0);
}

void	choose_fork(t_info *g_data, int th_nbr, int fork)
{
	if (fork == 1)
	{
		if (g_data->nb_philo == th_nbr + 1)
			print_logs(g_data, th_nbr, g_data->start_time, "has taken a fork");
		else
		{
			pthread_mutex_lock(&g_data->forks[th_nbr]);
			g_data->forks_status[th_nbr] = 1;
			print_logs(g_data, th_nbr, g_data->start_time, "has taken a fork");
		}
	}
	else if (fork == 2)
	{
		pthread_mutex_lock(&g_data->forks[next_fork_i(g_data, th_nbr)]);
		g_data->forks_status[next_fork_i(g_data, th_nbr)] = 1;
		if (g_data->nb_philo == th_nbr + 1)
		{
			pthread_mutex_lock(&g_data->forks[th_nbr]);
			g_data->forks_status[th_nbr] = 1;
		}
		print_logs(g_data, th_nbr, g_data->start_time, "has taken a fork");
	}
}

int	philo_actions(t_info *g_data, int th_nbr)
{
	if (taking_forks(g_data, th_nbr) == 1)
		return (1);
	if (eating(g_data, th_nbr) == 1)
		return (1);
	if (leaving_forks(g_data, th_nbr) == 1)
		return (1);
	if (sleeping(g_data, th_nbr) == 1)
		return (1);
	print_logs(g_data, th_nbr, g_data->start_time, "is thinking");
	return (0);
}
