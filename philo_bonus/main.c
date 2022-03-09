/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:59:18 by yang              #+#    #+#             */
/*   Updated: 2022/03/09 10:58:27 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_info(int argc, char *argv[], t_rules *rules)
{
	int	i;

	i = -1;
	if (check_arg(argv))
		return (1);
	rules->total = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->times_must_eat = ft_atoi(argv[5]);
	else
		rules->times_must_eat = -1;
	rules->is_died = 0;
	return (0);
}

/* Named semaphore: provide access to a resource between multiple processes
sem_unlink: removed specified name semaphore in the kernal
sem_open: create a named semaphore */

static void init_sem(t_rules *rules)
{
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/lock_info");
	rules->fork = sem_open("/fork", O_CREAT, 0644, rules->total);
	rules->print = sem_open("/print", O_CREAT, 0644, 1);
	rules->lock_info = sem_open("/lock_info", O_CREAT, 0644, 1);
}

int	init(int argc, char *argv[], t_rules *rules)
{
	int	i;

	if (parse_info(argc, argv, rules))
		return (1);
	i = -1;
	rules->philo = malloc(sizeof(t_philo) * rules->total);
	rules->pid = malloc(sizeof(pid_t) * rules->total);
	if (!rules->philo)
		return (1);
	while (++i < rules->total)
	{
		rules->philo[i].id = i;
		rules->philo[i].count_meal = 0;
		rules->philo[i].last_meal = 0;
		rules->philo[i].rules = rules;
	}
	init_sem(rules);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_rules			rules;

	if (argc == 5 || argc == 6)
	{
		if (init(argc, argv, &rules))
		{
			printf("Error occurred when intializing thread\n");
			return (1);
		}
		philosopher(&rules);
		return (0);
	}
	else
	{
		printf(BRED"Incorrect arguments.\n\n");
		return (1);
	}
}
