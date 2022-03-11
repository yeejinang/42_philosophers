/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:02:19 by yang              #+#    #+#             */
/*   Updated: 2022/03/11 21:14:34 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork[philo->first_fork]));
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->fork[philo->second_fork]);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->lock_info);
	print_state(philo, "is eating");
	philo->last_meal = current_time(philo->info->start_time);
	pthread_mutex_unlock(&philo->info->lock_info);
	ft_usleep(philo->info->time_to_eat);
	philo->count_meal++;
}

static void	putdown_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->fork[philo->first_fork]);
	pthread_mutex_unlock(&philo->info->fork[philo->second_fork]);
}

static void	*routine(void *argc)
{
	t_philo	*philo;

	philo = (t_philo *)argc;
	if (!(philo->id % 2))
		ft_usleep(philo->info->time_to_eat);
	while (!philo->info->is_died)
	{
		pickup_fork(philo);
		putdown_fork(philo);
		if (philo->count_meal == philo->info->times_must_eat)
		{
			pthread_mutex_lock(&philo->info->lock_info);
			philo->info->done_eat++;
			printf("done eat: %d\n", philo->info->done_eat);
			pthread_mutex_unlock(&philo->info->lock_info);
			break ;
		}
		print_state(philo, "is sleeping");
		ft_usleep(philo->info->time_to_sleep);
		print_state(philo, "is thinking");
	}
	return (NULL);
}

static int	exit_routine(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->total)
	{
		if (pthread_join(info->tid[i], NULL))
			return (1);
	}
	i = -1;
	while (++i < info->total)
	{
		if (pthread_mutex_destroy(&info->fork[i]))
			return (1);
	}
	if (pthread_mutex_destroy(&info->print)
		|| pthread_mutex_destroy(&info->lock_info))
		return (1);
	free_exit(info);
	return (0);
}

int	philosopher(t_info *info)
{
	int			i;

	i = -1;
	info->start_time = get_time();
	while (++i < info->total)
	{
		info->philo[i].info = info;
		if (pthread_create(&info->tid[i], NULL, &routine, &(info->philo[i])))
		{
			printf("Error occurred when creating threads\n");
			free_exit(info);
			return (1);
		}
	}
	check_death(info);
	if (exit_routine(info))
	{
		printf("Error occurred when exiting threads\n");
		free_exit(info);
		return (1);
	}
	return (0);
}
