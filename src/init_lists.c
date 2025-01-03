/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:28:43 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/03 16:31:29 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_lists(t_info *g_data)
{
	g_data->nb_philo = 0;
	g_data->t_die = 0;
	g_data->t_eat = 0;
	g_data->t_sleep = 0;
	g_data->nb_cycles = 0;
	g_data->time_passed = 0;
    g_data->thread_count = 0;
	g_data->thread_dead = 0;
}
