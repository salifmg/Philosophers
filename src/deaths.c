/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deaths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:45:10 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/03 17:45:40 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void check_threads(t_info *g_data, t_timeval current_time)
{
	int	i;

	i = 0;
	while (check_death(g_data, g_data->time_passed[i++], current_time) == 0)
	{
		if (i == g_data->nb_philo)
			i = 0;
	}
}

int	check_death(t_info *g_data, long time_passed, t_timeval current_time)
{
	if (time_passed >= g_data->t_die)
	{
		g_data->thread_dead = 1;
		printf("%ld %d died", current_time.tv_usec, g_data->thread_count); // unlock les mutex 
		return (1);
	}
	else if (g_data->thread_dead)
		return (2);
	return (0);
}
