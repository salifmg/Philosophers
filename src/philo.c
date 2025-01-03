/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:27:11 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/03 18:28:22 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eating(t_info *g_data, t_timeval current_time)
{
	long	t_left_eat;
	
	t_left_eat = g_data->t_eat;
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
	long	time_passed; // en ms ou convertis, efface
	int		loop_count;
	int		thread_num;
	t_info *g_data;
	t_timeval current_time; //efface

	loop_count = 0;
	time_passed = 0; // UTILISE | TEMPS PASSE ENTRE CHAQUE REPAS

	g_data = (t_info *)param;
	thread_num = g_data->thread_count - 1;
	gettimeofday(&current_time, NULL); // efface
	pthread_mutex_lock(&sync_order);
	usleep(1);
	pthread_mutex_unlock(&sync_order);

	if (check_death(g_data, time_passed, current_time) != 0)
		return (1);
// mutex chaque ecriture et fonction  %d is eating", current_time.tv_usec, g_data->thread_count); //ptetre dans eating | usec * 1000
	usleep(g_data->t_eat);
	if (eating(g_data, current_time) == 1)
		return (1);
	leaving_forks(g_data, thread_num, current_time);


	printf("%ld %d is sleeping", current_time.tv_usec, g_data->thread_count); //check mort avec fonction
	usleep(g_data->t_sleep);


	printf("%ld %d is thinking", current_time.tv_usec, g_data->thread_count);  

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
{// mutex chaque ecriture et fonction 
	t_timeval	current_time;
	int			i;

	i = 0;
	pthread_mutex_init(&sync_order, NULL);
	init_lists(g_data);
	forks = malloc(sizeof(pthread_mutex_t) * g_data->nb_philo);
	if (!forks)
		return (1);
	forks_creation(g_data);
	threads_creation(g_data, philo_data);
	gettimeofday(&current_time, NULL);
	check_threads(g_data, current_time);
	delete_threads(g_data, philo_data);
	delete_mutexes(g_data);
	free(forks);
	return (0);
}
