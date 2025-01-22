/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:34:00 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/22 20:17:02 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	leaving_taken_fork(t_info *g_data, int th_nbr)
{
	g_data->forks_status[th_nbr] = 0;
	pthread_mutex_unlock(&g_data->forks[th_nbr]);
}

int forks_availabity(t_info *g_data, int th_nbr, int part)
{
	if (part == 1)
	{
		while (1)
		{
			pthread_mutex_lock(&g_data->forks[th_nbr]);
			if (g_data->forks_status[th_nbr] == 1)
			{
				pthread_mutex_unlock(&g_data->forks[th_nbr]);
				pthread_mutex_lock(&g_data->check_dead);
				if (g_data->thread_dead == 1)
				{
					pthread_mutex_unlock(&g_data->check_dead);
					return (1);
				}
				pthread_mutex_unlock(&g_data->check_dead);
				usleep(50); //plus gros ou ptit
			}
			else
			{
				pthread_mutex_unlock(&g_data->forks[th_nbr]);
				break ;
			}
		}
	}
	else if (part == 2)
	{
		while (1)
		{
			pthread_mutex_lock(&g_data->forks[next_fork_index(g_data, th_nbr)]);
			if (g_data->forks_status[next_fork_index(g_data, th_nbr)] == 1)
			{
				pthread_mutex_unlock(&g_data->forks[next_fork_index(g_data, th_nbr)]);
				pthread_mutex_lock(&g_data->check_dead);
				if (g_data->thread_dead == 1)
				{
					pthread_mutex_unlock(&g_data->check_dead);
					leaving_taken_fork(g_data, th_nbr);
					return (1);
				}
				pthread_mutex_unlock(&g_data->check_dead);
				usleep(50); //plus gros ou ptit
			}
			else
			{
				pthread_mutex_unlock(&g_data->forks[next_fork_index(g_data, th_nbr)]);
				break ;
			}
		}
	}
	return (0);
}

int	leaving_forks(t_info *g_data, int th_nbr)
{
	if (g_data->forks_status[th_nbr] == 1)
	{
		g_data->forks_status[th_nbr] = 0;
		pthread_mutex_unlock(&g_data->forks[th_nbr]);
	}
	if (g_data->forks_status[next_fork_index(g_data, th_nbr)] == 1)
	{
		g_data->forks_status[next_fork_index(g_data, th_nbr)] = 0;
		pthread_mutex_unlock(&g_data->forks[next_fork_index(g_data, th_nbr)]);
	}
	pthread_mutex_lock(&g_data->check_dead);
	if (g_data->thread_dead == 1)
		return (1);
	pthread_mutex_unlock(&g_data->check_dead);
	return (0);
}

int	taking_forks(t_info *g_data, int th_nbr)
{
	pthread_mutex_lock(&g_data->check_dead);
	if (g_data->thread_dead == 1)
	{
		pthread_mutex_unlock(&g_data->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&g_data->check_dead);
	if (g_data->nb_philo == 1)
		return (single_fork(g_data, th_nbr));
	if (forks_availabity(g_data, th_nbr, 1) == 1)
		return (1);
	pthread_mutex_lock(&g_data->forks[th_nbr]);
	g_data->forks_status[th_nbr] = 1;
	print_logs(g_data, th_nbr, g_data->start_time, "has taken a fork");
	pthread_mutex_lock(&g_data->check_dead);
	if (g_data->thread_dead == 1)
	{
		leaving_taken_fork(g_data, th_nbr);
		pthread_mutex_unlock(&g_data->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&g_data->check_dead);
	if (forks_availabity(g_data, th_nbr, 2) == 1)
		return (1);
	pthread_mutex_lock(&g_data->forks[next_fork_index(g_data, th_nbr)]);
	g_data->forks_status[next_fork_index(g_data, th_nbr)] = 1;
	print_logs(g_data, th_nbr, g_data->start_time, "has taken a fork");
	pthread_mutex_lock(&g_data->check_dead);
	if (g_data->thread_dead == 1)
	{
		pthread_mutex_unlock(&g_data->check_dead);
		return (leaving_forks(g_data, th_nbr));
	}
	pthread_mutex_unlock(&g_data->check_dead);
	return (0);
}

int	single_fork(t_info *g_data, int th_nbr)
{
	// pthread_mutex_lock(&g_data->forks[th_nbr]);
	print_logs(g_data, th_nbr, g_data->start_time, "has taken a fork");
	while (1)
	{
		pthread_mutex_lock(&g_data->check_dead);
		if (g_data->thread_dead == 1)
			break ;
		pthread_mutex_unlock(&g_data->check_dead);
		usleep(50);
	}
	pthread_mutex_unlock(&g_data->check_dead);
	// pthread_mutex_unlock(&g_data->forks[th_nbr]);
	printf("fini fork\n");
	return (1);
}
