/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:27:11 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/06 18:50:23 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eating(t_info *g_data, t_timeval current_time)
{
	long	t_left_eat;
	
	t_left_eat = g_data->t_eat;
	print_logs(g_data, current_time, " is eating");
	while (t_left_eat)
	{
		if (check_death(g_data, t_left_eat, current_time) != 0)
			return (1);
		if (9 < g_data->t_eat)
		{
			usleep(9);
			t_left_eat -= 9;
		}
		else
		{
			usleep(t_left_eat);
			t_left_eat -= t_left_eat;
		}
	}
	return (0);
}

void *philo(void *param)
{
	long		time_passed; // en ms ou convertis, efface
	int			loop_count;
	int			thread_num;
	char		*order;
	t_info		*g_data;
	t_timeval	current_time; //efface

	loop_count = 0;
	time_passed = 0; // UTILISE | TEMPS PASSE ENTRE CHAQUE REPAS

	g_data = (t_info *)param;
	thread_num = g_data->thread_count - 1;
	gettimeofday(&current_time, NULL); // efface
	pthread_mutex_lock(&sync_order);
	usleep(1);
	pthread_mutex_unlock(&sync_order);

// mutex chaque ecriture et fonction  %d is eating", current_time.tv_usec, g_data->thread_count); //ptetre dans eating | usec * 1000
	taking_forks(g_data, thread_num, current_time);
	usleep(g_data->t_eat);
	if (eating(g_data, current_time) == 1)
		return (1);
	leaving_forks(g_data, thread_num);

	print_logs(g_data, current_time, " is sleeping"); //check mort avec fonction
	usleep(g_data->t_sleep);

	print_logs(g_data, current_time, " is thinking"); //check mort avec fonction 

	/* 	if (loop_count)
	{
		while (loop_count != g_data->nb_cycles)
		{

		}
	}
	else
	{
		while (1)
		{

		}
	} */
}

int philosophers_creation(t_info *g_data, t_philo *philo_data)
{
	t_timeval	current_time; //efface les tous ICI

	pthread_mutex_init(&sync_order, NULL);
	pthread_mutex_init(&writing, NULL);
	init_lists(g_data);
	if (forks_creation(g_data) == 1)
		return (1);
	threads_creation(g_data, philo_data);
	gettimeofday(&current_time, NULL);//efface les tous ICI
	check_philos(g_data, current_time);//efface les tous ICI
	delete_threads(g_data, philo_data);
	delete_mutexes(g_data);
	free(forks);
	free(g_data->forks_status);
	return (0);
}
