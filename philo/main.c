/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:59:18 by yang              #+#    #+#             */
/*   Updated: 2022/02/23 10:59:48 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_info(int argc, char *argv[], t_rules *rules)
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

void	set_fork(t_rules *rules, t_philo *philo)
{
	int	temp;

	philo->first_fork = philo->id;
	philo->second_fork = (philo->id + 1) % (rules->total);
	if (philo->second_fork < philo->first_fork)
	{
		temp = philo->first_fork;
		philo->first_fork = philo->second_fork;
		philo->second_fork = temp;
		philo->state = HUNGRY;
	}
}

int init(t_rules *rules)
{
	int	i;

	i = -1;
	rules->philo = (t_philo *)malloc(sizeof(t_philo) * rules->total);
	rules->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * rules->total);
	rules->tid = (pthread_t *)malloc(sizeof(pthread_t) * rules->total);
	if (!rules->philo || !rules->fork || !rules->tid)
		return (1);
	while (++i < rules->total)
	{
		rules->philo[i].id = i;
		rules->philo[i].count_meal = 0;
		rules->philo[i].last_meal = 0;
		set_fork(rules, &rules->philo[i]);
		if (pthread_mutex_init(&rules->fork[i], NULL))
			return (1);
	}
	if (pthread_mutex_init(&rules->print, NULL) || pthread_mutex_init(&rules->death, NULL)
		|| pthread_mutex_init(&rules->lock, NULL))
		return (1);
	return (0);
}

int main(int argc, char *argv[])
{
	t_rules			rules;

	if (argc == 5 || argc == 6)
	{
		if (parse_info(argc, argv, &rules))
			return (1);
		if (init(&rules))
		{
			printf("Error occurred when creating thread\n");
			return (1);
		}
		philosopher(&rules);
		return (0);
	}
	else
	{
		printf(BRED"Incorrect arguments.\n\n");
		printf(BYEL"Arguments have to be formatted as below:\n");
		printf(BLU"./philo [number_of_philosphers] [time_to_die] [time_to_eat] ");
		printf(BLU"[time_to_sleep] [(OPTIONAL)number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
}
