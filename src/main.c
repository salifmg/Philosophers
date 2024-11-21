/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:05:09 by smagassa          #+#    #+#             */
/*   Updated: 2024/11/21 18:19:08 by smagassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5)
	{
		write(2, "<Nb_philo> <T_die> <T_eat> <T_sleep> [Nb_cycles]", 49);
		return (1);
	}
	while (av[i])
	{
		if (!ft_atoi(av[i]))
		{
			write(2, "ONLY INSERT POSITIVE NUMBERS AS ARGS", 28);
			return (1);
		}
		i++;
	}
	philosophers(av);
	return (0);
}
