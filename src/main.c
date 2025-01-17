/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:05:09 by smagassa          #+#    #+#             */
/*   Updated: 2025/01/17 15:38:44 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	args_lists(t_info *g_data, int ac, char **param)
{
	int	i;

	i = 0;
	while (ac > ++i)
	{
		if (ft_atoi(param[i]) <= 0)
		{
			write(2, "ONLY INSERT POSITIVE NUMBERS AS ARGS", 36);
			exit(1);
		}
	}
	g_data->nb_philo = ft_atoi(param[1]);
	g_data->t_die = ft_atoi(param[2]);
	g_data->t_eat = ft_atoi(param[3]);
	g_data->t_sleep = ft_atoi(param[4]);
	if (ac == 6)
		g_data->nb_cycles = ft_atoi(param[5]);
	else
		g_data->nb_cycles = 0;
}

int	main(int ac, char **av)
{
	t_philo	*philo_data;
	t_info	g_data;

	if (ac != 5 && ac != 6)
	{
		write(2, "<Nb_philo> <T_die> <T_eat> <T_sleep> [Nb_cycles]", 49);
		return (1);
	}
	args_lists(&g_data, ac, av);
	philo_data = malloc(sizeof(t_info) * g_data.nb_philo);
	if (!philo_data)
		return (perror("Failed to allocate memory for philosophers"), 1);
	if (g_data.nb_philo == 1)
	{
		if (single_philosopher(&g_data, philo_data) != 0)
			return (free(philo_data), 1);
	}
	else if (philosophers_creation(&g_data, philo_data) != 0)
		return (free(philo_data), 1);
	free(philo_data);
	return (0);
}
