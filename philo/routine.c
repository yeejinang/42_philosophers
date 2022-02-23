/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:02:19 by yang              #+#    #+#             */
/*   Updated: 2022/02/23 11:57:45 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup_fork(t_philo *philo)
{
	/*int		id;
	t_philo	left;
	t_philo	right;
	int		total;

	id = philo->id;
	total = philo->rules->total;
	left = philo->rules->philo[(id - 1 + total) % total];
	right = philo->rules->philo[(id + 1) % total];
	while (philo->state == HUNGRY)
	{
		if (left.state != EATING && right.state != EATING)
		{*/
			pthread_mutex_lock(&(philo->rules->fork[philo->first_fork]));
			print_state(philo, PICK_FORK);
			pthread_mutex_lock(&philo->rules->fork[philo->second_fork]);
			print_state(philo, PICK_FORK);
			philo->state = EATING;
		//}
	//}
}

void	putdown_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rules->fork[philo->first_fork]);
	pthread_mutex_unlock(&philo->rules->fork[philo->second_fork]);
}

void	*routine(void *argc)
{
	t_philo	*philo = (t_philo *)argc;

	if (!(philo->id % 2))
		ft_usleep(philo->rules->time_to_eat);
	while (philo->rules->is_died != 1)
	{
		pickup_fork(philo);
		print_state(philo, EATING);
		philo->count_meal++;
		philo->last_meal = current_time(philo->rules->start_time) + philo->rules->time_to_eat;
		ft_usleep(philo->rules->time_to_eat);
		//philo->last_meal = current_time(philo->rules->start_time);
		putdown_fork(philo);
		print_state(philo, SLEEPING);
		ft_usleep(philo->rules->time_to_sleep);
		philo->state = HUNGRY;
		print_state(philo, THINKING);
	/*if (philo->rules->times_must_eat != -1
			&& philo->count_meal < philo->rules->times_must_eat)
			break;*/
	}
	return (NULL);
}

int	exit_routine(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->total)
	{
		if (pthread_join(rules->tid[i], NULL))
			return (1);
		if (pthread_mutex_destroy(&rules->fork[i]))
			return (1);
	}
	if (pthread_mutex_destroy(&rules->print) || pthread_mutex_destroy(&rules->death)
		|| pthread_mutex_destroy(&rules->lock))
		return (1);
	free(rules->tid);
	free(rules->philo);
	free(rules->fork);
	return (0);
}

int	philosopher(t_rules *rules)
{
	int			i;

	i = -1;
	rules->start_time = get_time();
	while (++i < rules->total)
	{
		rules->philo[i].rules = rules;
		if (pthread_create(&rules->tid[i], NULL, &routine, &(rules->philo[i])))
		{
			printf("Error occurred when creating threads\n");
			free(rules->tid);
			free(rules->philo);
			free(rules->fork);
			return (1);
		}
		usleep(1000);
	}
	check_death(rules);
	if (exit_routine(rules))
	{
		printf("Error occurred when exiting threads\n");
	}
	return (0);
}
