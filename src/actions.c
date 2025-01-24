/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:13:58 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/24 18:25:11 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	philo_actions(t_info *g_data, int th_nbr)
{
	if (taking_forks(g_data, th_nbr) == 1)
		return (1);
	if (eating(g_data, th_nbr) == 1)
		return (1);
	if (leaving_forks(g_data, th_nbr) == 1)
		return (1);
	if (sleeping(g_data, th_nbr) == 1)
		return (1);
	print_logs(g_data, th_nbr, g_data->start_time, "is thinking");
	return (0);
}
