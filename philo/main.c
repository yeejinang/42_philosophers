/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:59:18 by yang              #+#    #+#             */
/*   Updated: 2022/03/11 18:00:57 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_info(int argc, char *argv[], t_info *info)
{
	int	i;

	i = -1;
	if (check_arg(argv))
		return (1);
	info->total = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->times_must_eat = ft_atoi(argv[5]);
	else
		info->times_must_eat = -1;
	info->is_died = 0;
	info->done_eat = 0;
	return (0);
}

static void	set_fork(t_info *info, t_philo *philo)
{
	int	temp;

	philo->first_fork = philo->id;
	philo->second_fork = (philo->id + 1) % (info->total);
	if (philo->second_fork < philo->first_fork)
	{
		temp = philo->first_fork;
		philo->first_fork = philo->second_fork;
		philo->second_fork = temp;
	}
}

int	init(int argc, char *argv[], t_info *info)
{
	int	i;

	if (parse_info(argc, argv, info))
		return (1);
	i = -1;
	info->philo = malloc(sizeof(t_philo) * info->total);
	info->fork = malloc(sizeof(pthread_mutex_t) * info->total);
	info->tid = malloc(sizeof(pthread_t) * info->total);
	if (!info->philo || !info->fork || !info->tid)
		return (1);
	while (++i < info->total)
	{
		info->philo[i].id = i;
		info->philo[i].count_meal = 0;
		info->philo[i].last_meal = 0;
		info->philo[i].info = info;
		set_fork(info, &info->philo[i]);
		if (pthread_mutex_init(&info->fork[i], NULL))
			return (2);
	}
	if (pthread_mutex_init(&info->print, NULL)
		|| pthread_mutex_init(&info->lock_info, NULL))
		return (2);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	int		res;

	if (argc == 5 || argc == 6)
	{
		res = init(argc, argv, &info);
		if (res)
		{
			printf("Error occurred when intializing thread\n");
			if (res == 2)
				free_exit(&info);
			return (1);
		}
		philosopher(&info);
		return (0);
	}
	else
	{
		printf(BRED"Incorrect arguments.\n");
		return (1);
	}
}
