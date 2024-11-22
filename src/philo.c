/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:27:11 by smagassa          #+#    #+#             */
/*   Updated: 2024/11/22 18:01:37 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philosophers(char **param)
{
	
}

int philosophers_creation(t_info *general_data, t_philo *philo_data)
{
	int	i;

	i = 0;
	while (i < general_data->nb_philo)
		pthread_create(&philo_data[i++].threads, NULL, &philosophers, general_data);
}
