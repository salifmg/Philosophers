/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:27:11 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/02 20:40:27 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_info *g_data, long time_passed, t_timeval current_time)
{
	if (time_passed >= g_data->t_die)
	{
		g_data->thread_dead = 1;
		printf("%ld %d died", current_time.tv_usec, g_data->thread_count); 
		return (1);
	}
	else if (g_data->thread_dead)
		return (2);
	return (0);
}

int	eating(t_info *g_data, t_timeval current_time)
{
	long t_left_eat;
	
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
	long	time_passed;
	int		loop_count;
	int		thread_num;
	t_info *g_data;
	t_timeval current_time;

	loop_count = 0;
	time_passed = 0; // UTILISE | TEMPS PASSE ENTRE CHAQUE REPAS
	g_data = (t_info *)param;
	thread_num = g_data->thread_count - 1;
	gettimeofday(&current_time, NULL);
    pthread_mutex_lock(&sync_order);
	usleep(1);
	pthread_mutex_unlock(&sync_order);
	if (check_death(g_data, time_passed, current_time) != 0)
		return (1);


	taking_forks(g_data, thread_num, current_time);
	printf("%ld %d is eating", current_time.tv_usec, g_data->thread_count); //ptetre dans eating
	if (eating(g_data, current_time) == 1)
		return (1);
	leaving_forks(g_data, thread_num, current_time);


	//CHECK MORT
	printf("%ld %d is sleeping", current_time.tv_usec, g_data->thread_count); 
	usleep(g_data->t_sleep);
	//CHECK MORT

	if (fork_status[(thread_num + 1) % g_data->nb_philo] == 1)
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
{
	int	i;

	i = 0;
	pthread_mutex_init(&sync_order, NULL);
	pthread_mutex_lock(&sync_order);
	forks = malloc(sizeof(pthread_mutex_t) * g_data->nb_philo);
	if (!forks)
		return (1);
	while (i < g_data->nb_philo)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    pthread_mutex_lock(&sync_order);

	g_data->thread_dead = 0; // pas sur avc l'autre
    g_data->thread_count = 0;

	i = 0;
	while (i < g_data->nb_philo)
	{
		g_data->thread_count += 1;
		if (pthread_create(&philo_data[i++].threads, NULL, &philo, g_data) != 0)
		{
			perror("Failed to create a thread");
			return (2);
		}
	}
	pthread_mutex_unlock(&sync_order);
	i = 0;
	while (i < g_data->nb_philo)
	{
		if ((pthread_join(philo_data[i++].threads, NULL) != 0))
		{
			perror("Failed to join all threads");
			return (3);
		}
	}
	pthread_mutex_destroy(&sync_order);
	i = 0;
    while (i < g_data->nb_philo)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    free(forks);
    return (0);
}
