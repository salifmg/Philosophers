/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:34:00 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/13 16:30:49 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	forks_availabity(t_info *g_data, int th_nbr, int part)
{
	if (part == 1)
	{
		while (g_data->forks_status[(th_nbr + 1) % g_data->nb_philo] == 1)
		{
			if (g_data->thread_dead == 1)
				return (1);
			usleep(50); //plus gros ou ptit
		}
	}
	else if (part == 2)
	{
		while (g_data->forks_status[th_nbr] == 1)
		{
			if (g_data->thread_dead == 1)
			{
				pthread_mutex_unlock(&g_data->forks[(th_nbr + 1)
					% g_data->nb_philo]);
				g_data->forks_status[(th_nbr + 1) % g_data->nb_philo] = 0;
				return (1);
			}
			usleep(50); //plus gros ou ptit
		}
	}
	return (0);
}

int	leaving_forks(t_info *g_data, int th_nbr)
{
	if (g_data->forks_status[(th_nbr + 1) % g_data->nb_philo] == 1)
	{
		pthread_mutex_unlock(&g_data->forks[(th_nbr + 1) % g_data->nb_philo]);
		g_data->forks_status[(th_nbr + 1) % g_data->nb_philo] = 0;
	}
	if (g_data->forks_status[th_nbr] == 1)
	{
		pthread_mutex_unlock(&g_data->forks[th_nbr]);
		g_data->forks_status[th_nbr] = 0;
	}
	if (g_data->thread_dead == 1)
		return (1);
	return (0);
}

int	taking_forks(t_info *g_data, int th_nbr)
{
	if (g_data->thread_dead == 1)
		return (1);
	if (g_data->nb_philo == 1)
		return (single_fork(g_data, th_nbr));
	if (forks_availabity(g_data, th_nbr, 1) == 1)
		return (1);
	pthread_mutex_lock(&g_data->forks[(th_nbr + 1) % g_data->nb_philo]);
	g_data->forks_status[(th_nbr + 1) % g_data->nb_philo] = 1;
	print_logs(g_data, th_nbr, g_data->start_time, "has taken a fork");
	if (forks_availabity(g_data, th_nbr, 2) == 1)
		return (1);
	pthread_mutex_lock(&g_data->forks[th_nbr]);
	g_data->forks_status[th_nbr] = 1;
	print_logs(g_data, th_nbr, g_data->start_time, "has taken a fork");
	if (g_data->thread_dead == 1)
		return (leaving_forks(g_data, th_nbr));
	return (0);
}

int	single_fork(t_info *g_data, int th_nbr)
{
	pthread_mutex_lock(&g_data->forks[th_nbr]);
	print_logs(g_data, th_nbr, g_data->start_time, "has taken a fork");
	while (g_data->thread_dead == 0)
		usleep(50);
	pthread_mutex_unlock(&g_data->forks[th_nbr]);
	return (1);
}
