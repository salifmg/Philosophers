/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:05:09 by smagassa          #+#    #+#             */
/*   Updated: 2024/12/31 14:34:14 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_num(const char str)
{
	if (str >= '0' && str <= '9')
		return (1);
	else
		return (0);
}

int	is_char(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_num(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (is_char(&str[i]) == 0)
		return (0);
	return (result * sign);
}

void args_lists(t_info *g_data, int ac, char **param)
{
	int	i;

	i = 0;
	while (ac > ++i)
	{
		if (!ft_atoi(param[i]))
		{
			write(2, "ONLY INSERT POSITIVE NUMBERS AS ARGS", 28);
			return (1);
		}
	}
	g_data->nb_philo = param[1];
	g_data->t_die = param[2];
	g_data->t_eat = param[3];
	g_data->t_sleep = param[4];
	if (ac == 6)
		g_data->nb_cycles = param[5];
}

int main(int ac, char **av)
{
	t_philo	*philo_data;
	t_info	g_data;

	if (ac == 5 || ac == 6)
	{
		write(2, "<Nb_philo> <T_die> <T_eat> <T_sleep> [Nb_cycles]", 49);
		return (1);
	}
	args_lists(&g_data, ac, av);
	philosophers_creation(&g_data, philo_data);
	//pthread_join(&philo_data[i]->threads, NULL);

	return (0);
}
