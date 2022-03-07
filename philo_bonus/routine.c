/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:02:19 by yang              #+#    #+#             */
/*   Updated: 2022/03/07 15:39:51 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pickup_fork(t_philo *philo)
{
	sem_wait(philo->rules->fork);
	print_state(philo, "has taken a fork");
	sem_wait(philo->rules->fork);
	print_state(philo, "has taken a fork");
	sem_wait(philo->rules->lock_info);
}

static void	putdown_fork(t_philo *philo)
{
	sem_post(&philo->rules->fork[philo->first_fork]);
	pthread_mutex_unlock(&philo->rules->fork[philo->second_fork]);
}

static void	*routine(void *argc)
{
	t_philo	*philo;

	philo = (t_philo *)argc;
	if (!(philo->id % 2))
		ft_usleep(philo->rules->time_to_eat);
	while (philo->rules->is_died != 1)
	{
		pickup_fork(philo);
		print_state(philo, "is eating");
		philo->last_meal = current_time(philo->rules->start);
		pthread_mutex_unlock(&philo->rules->lock_info);
		ft_usleep(philo->rules->time_to_eat);
		philo->count_meal++;
		putdown_fork(philo);
		if (philo->rules->is_died)
			break ;
		print_state(philo, "is sleeping");
		ft_usleep(philo->rules->time_to_sleep);
		print_state(philo, "is thinking");
	}
	return (NULL);
}

static int	exit_routine(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->total)
	{
		if (pthread_join(rules->tid[i], NULL))
			return (1);
	}
	i = -1;
	while (++i < rules->total)
	{
		if (pthread_mutex_destroy(&rules->fork[i]))
			return (1);
	}
	if (pthread_mutex_destroy(&rules->print)
		|| pthread_mutex_destroy(&rules->lock_info))
		return (1);
	free_exit(rules);
	return (0);
}

int	philosopher(t_rules *rules)
{
	int			i;

	i = -1;
	rules->start = get_time();
	while (++i < rules->total)
	{
		rules->philo[i].rules = rules;
		if (pthread_create(&rules->tid[i], NULL, &routine, &(rules->philo[i])))
		{
			printf("Error occurred when creating threads\n");
			free_exit(rules);
			return (1);
		}
	}
	check_death(rules);
	if (exit_routine(rules))
	{
		printf("Error occurred when exiting threads\n");
		free_exit(rules);
	}
	return (0);
}
