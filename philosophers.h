/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:03:25 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/02 20:14:48 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

typedef struct timeval t_timeval;
pthread_mutex_t sync_order;
pthread_mutex_t *forks;
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct s_info
{
	int	nb_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nb_cycles;

	int thread_count;
	int thread_dead;
}						t_info;

typedef struct s_philo
{
	pthread_t	threads;
}						t_philo;

int	ft_atoi(const char *str);
int	is_char(const char *str);
int	is_num(const char str);

#endif