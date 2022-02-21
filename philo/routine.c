/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:02:19 by yang              #+#    #+#             */
/*   Updated: 2022/02/21 18:56:52 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *argc)
{
	t_philo	*philo = (t_philo *)argc;

	while (philo->rules->is_died != 1 && philo->count_meal < philo->rules->times_must_eat)
	{
		pickup_fork(philo);
		//printf("Philo %d has taken a fork %d\n", argc->id, argc->second_fork);
		print_state(philo, EATING);
		philo->count_meal++;
		//printf("Philo %d is eating\n", argc->id);
		usleep(philo->rules->time_to_eat);
		philo->last_meal = current_time(philo->rules->start_time);
		printf("last meal: %ld\n", philo->last_meal);
		putdown_fork(philo);
		print_state(philo, SLEEPING);
		//printf("Philo %d had put down the fork %d\n", argc->id, argc->second_fork);
		//printf("Philo %d is sleeping\n", argc->id);
		usleep(philo->rules->time_to_sleep);
		print_state(philo, THINKING);
	}
	return (NULL);
}

void	pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->fork[philo->first_fork]);
	print_state(philo, PICK_FORK);
	pthread_mutex_lock(&philo->rules->fork[philo->second_fork]);
	print_state(philo, PICK_FORK);
}

void	putdown_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rules->fork[first_fork]);
	pthread_mutex_unlock(&philo->rules->fork[second_fork]);
}

void	*routine(void *argc)
{
	t_philo	*philo = (t_philo *)argc;

	while (philo->rules->is_died != 1)
	{
		pickup_fork(philo);
		//printf("Philo %d has taken a fork %d\n", argc->id, argc->second_fork);
		print_state(philo, EATING);
		philo->count_meal++;
		//printf("Philo %d is eating\n", argc->id);
		usleep(philo->rules->time_to_eat);
		philo->last_meal = current_time(philo->rules->start_time);
		printf("last meal: %ld\n", philo->last_meal);
		putdown_fork(philo);
		print_state(philo, SLEEPING);
		//printf("Philo %d had put down the fork %d\n", argc->id, argc->second_fork);
		//printf("Philo %d is sleeping\n", argc->id);
		usleep(philo->rules->time_to_sleep);
		print_state(philo, THINKING);
	}
	return (NULL);
}

int	philo(t_rules *rules)
{
	int	i;
	pthread_t	tid[rules->total_philos];

	i = -1;
	while (++i < rules->total_philos)
	{
		if (pthread_create(&tid, NULL, routine, (void *)philo[i]))
		{
			printf("Error occurred when creating threads\n");
			return (1);
		}
	}
	return (0);
}
