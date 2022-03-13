/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:37:00 by yang              #+#    #+#             */
/*   Updated: 2022/03/12 13:48:56 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *argc)
{
	long	last_meal;
	t_philo	*philo;

	philo = (t_philo *)argc;
	while (1)
	{
		sem_wait(philo->info->lock_info);
		last_meal = current_time(philo->info->start_time) - philo->last_meal;
		if (last_meal > philo->info->time_to_die)
		{
			printf(BRED);
			print_state(philo, "died");
			sem_post(philo->info->death);
			sem_post(philo->info->lock_info);
			exit(0);
		}
		sem_post(philo->info->lock_info);
		usleep (100);
	}
	return (NULL);
}

void	*check_meal(void *argc)
{
	int		i;
	t_info	*info;

	i = -1;
	info = (t_info *)argc;
	if (info->times_must_eat != -1)
	{
		while (++i < info->total)
			sem_wait(info->lock_meal);
		printf(BLU"Philosophers have eaten %d times.\n", info->times_must_eat);
		sem_post(info->death);
	}
	return (argc);
}
