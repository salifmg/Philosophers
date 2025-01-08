/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:03:25 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/08 17:28:02 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval t_timeval;

typedef struct s_info
{
	long	*time_passed;
	int		*forks_status;
	
	long	start_time;
	int		nb_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		nb_cycles;
	int		thread_count;
	int		thread_dead;
	
	pthread_mutex_t	sync_order;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*writing;
}						t_info;

typedef struct s_philo
{
	pthread_t		threads;
}						t_philo;

int	ft_atoi(const char *str);
int	is_char(const char *str);
int	is_num(const char str);

void	*philo(void *param);

time_t	get_ctime(void);

#endif
