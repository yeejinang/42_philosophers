/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:59:18 by yang              #+#    #+#             */
/*   Updated: 2022/03/11 12:42:27 by yang             ###   ########.fr       */
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
	return (0);
}

/* Named semaphore: provide access to a resource between multiple processes
sem_unlink: removed specified name semaphore in the kernal
sem_open: create a named semaphore */

static int	init_sem(t_info *info)
{
	sem_unlink("/fork");
	info->fork = sem_open("/fork", O_CREAT, 0644, info->total);
	sem_unlink("/print");
	info->print = sem_open("/print", O_CREAT, 0644, 1);
	sem_unlink("/lock_info");
	info->lock_info = sem_open("/lock_info", O_CREAT, 0644, 1);
	sem_unlink("/death");
	info->death = sem_open("/death", O_CREAT, 0644, 0);
	if (info->fork == SEM_FAILED || info->print == SEM_FAILED
		|| info->lock_info == SEM_FAILED || info->death == SEM_FAILED)
		return (1);
	return (0);
}

int	init(int argc, char *argv[], t_info *info)
{
	int	i;

	if (parse_info(argc, argv, info))
		return (1);
	i = -1;
	info->philo = malloc(sizeof(t_philo) * info->total);
	info->pid = malloc(sizeof(pid_t) * info->total);
	if (!info->philo)
		return (1);
	while (++i < info->total)
	{
		info->philo[i].id = i;
		info->philo[i].count_meal = 0;
		info->philo[i].last_meal = 0;
		info->philo[i].info = info;
	}
	if (init_sem(info))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info			info;

	if (argc == 5 || argc == 6)
	{
		if (init(argc, argv, &info))
		{
			printf(BRED"Error occurred when intializing thread\n");
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
