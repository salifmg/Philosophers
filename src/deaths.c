/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deaths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:45:10 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/12 16:20:38 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_death(t_info *g_data, long last_meal_time)
{
	long	now;
	long	elapsed_time;

	now = get_ctime();
	elapsed_time = now - g_data->start_time;
	if (now - last_meal_time >= g_data->t_die)
	{
		print_logs(g_data, elapsed_time, "died");
		return (1);
	}
	else if (g_data->thread_dead)
		return (2);
	return (0);
}

int	check_philos(t_info *g_data, int i)
{
	while (g_data->th_end != g_data->nb_philo && check_death(g_data,
			g_data->time_passed[i++]) == 0)
	{
		if (i == g_data->nb_philo)
			i = 0;
		usleep(50); //plus gros ou ptit
	}
	if (g_data->th_end == g_data->nb_philo)
		return (0);
	return (1);
}
