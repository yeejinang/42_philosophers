/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:09:26 by yang              #+#    #+#             */
/*   Updated: 2022/03/10 12:04:15 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atoi(const char *str)
{
	unsigned int	i;
	int				sign;
	long			result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '-' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (is_number(str[i]))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

static int	check_non_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!is_number(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_arg(char *argv[])
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (check_non_numeric(argv[i]))
			return (1);
	}
	return (0);
}

void	free_exit(t_info *info)
{
	free(info->tid);
	free(info->philo);
	free(info->fork);
}
