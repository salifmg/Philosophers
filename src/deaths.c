/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deaths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:45:10 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/07 17:56:50 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void check_philos(t_info *g_data, int i)
{
	while (check_death(g_data, g_data->time_passed[i++]) == 0)
	{
		if (i == g_data->nb_philo)
			i = 0;
		usleep(50); //delai ptetre plus grand
	}
}

int	check_death(t_info *g_data, long last_meal_time)
{
    long now;
    long elapsed_time;

    now = get_ctime();
    elapsed_time = now - g_data->start_time;
    if (now - last_meal_time >= g_data->t_die)
    {
        print_logs(g_data, elapsed_time, "died");
		// unlock les mutex tt les actions
        return (1);
    }
    else if (g_data->thread_dead)
        return (2);
    return (0);
}
