/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deaths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:45:10 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/06 19:27:50 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void check_philos(t_info *g_data)
{
	int	i;

	i = 0;
	while (check_death(g_data, g_data->time_passed[i++], g_data->start_time) == 0)
	{
		if (i == g_data->nb_philo)
			i = 0;
		//petit delai?
	}
}

int	check_death(t_info *g_data, long time_passed, long start_time)
{
    long now;
    long elapsed_time;

    now = get_ctime();
    elapsed_time = now - start_time;

    if (elapsed_time >= g_data->t_die)
    {
        print_logs(g_data, elapsed_time, "died");
        g_data->thread_dead = 1;
		// unlock les mutex
        return (1);
    }
    else if (g_data->thread_dead)
        return (2);
    return (0);
}
