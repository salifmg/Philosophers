/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:03:25 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/20 15:46:51 by smagassa         ###   ########.fr       */
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

typedef struct timeval	t_timeval;

typedef struct s_info
{
	long			*time_passed;
	long			start_time;

	int				*forks_status;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_cycles;
	int				thread_count;
	int				thread_dead;
	int				th_end;

	pthread_mutex_t	*forks;
	pthread_mutex_t	*all_time_passed;
	pthread_mutex_t	writing;
	pthread_mutex_t	sync_order;
	pthread_mutex_t	total_ended_th;
	pthread_mutex_t	check_dead;
}						t_info;

typedef struct s_philo
{
	pthread_t		threads;
}						t_philo;

typedef struct s_thread_param
{
	int				th_nbr;
	t_info			*g_data;
}				t_thread_param;

long	get_ctime(void);

int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *str);
int		is_char(const char *str);
int		is_num(const char str);
int		init_lists(t_info *g_data);

int		sleeping(t_info *g_data, int th_nbr);
int		eating(t_info *g_data, int th_nbr);

int		threads_creation(t_info *g_data, t_philo *philo_data);
int		delete_threads(t_info *g_data, t_philo *philo_data);
int		single_thread(t_info *g_data, t_philo *philo_data);
int		single_philosopher(t_info *g_data, t_philo *philo_data);
int		philosophers_creation(t_info *g_data, t_philo *philo_data);
int		philo_actions(t_info *g_data, int th_nbr);


int		forks_creation(t_info *g_data);
int		single_fork(t_info *g_data, int th_nbr);
int		taking_forks(t_info *g_data, int th_nbr);
int		leaving_forks(t_info *g_data, int th_nbr);
int		forks_availabity(t_info *g_data, int th_nbr, int part);
int		next_fork_index(t_info *g_data, int th_nbr);

int		check_death(t_info *g_data, long last_meal_time, int th_nbr);
int		check_philos(t_info *g_data);

void	delete_mutexes(t_info *g_data);
void	leaving_taken_fork(t_info *g_data, int th_nbr);
void	del_and_free(t_info *g_data, t_philo *philo_data, int part);
void	print_logs(t_info *g_data, int th_nbr, long start_time, char *order);
void	*philo(void *param);
void	ft_usleep(long ms);

#endif
