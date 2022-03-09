/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:34:40 by yang              #+#    #+#             */
/*   Updated: 2022/03/09 10:52:04 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *argc)
{
	long	last_meal;
	//long	last;
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)argc;
	rules = philo->rules;
	//printf("philo: %d is died: %d\n", philo->id, rules->is_died);
	while (rules->is_died == 0)
	{
		sem_wait(rules->lock_info);
		//printf("philo: %d is died: %d\n", philo->id, rules->is_died);
		last_meal = current_time(rules->start_time) - philo->last_meal;
		if (last_meal > rules->time_to_die || (rules->times_must_eat != -1
				&& philo->count_meal == rules->times_must_eat))
		{
			if (last_meal > rules->time_to_die)
				print_state(philo, "died");
			rules->is_died = 1;
			//philo->rules = rules;
			//printf("philo: %d is died: %d\n", philo->id, rules->is_died);
			sem_post(rules->lock_info);
			exit(1);
		}
		sem_post(rules->lock_info);
		usleep(100);
	}
	return (NULL);
}

void	print_state(t_philo *philo, char *str)
{
	long	time_stamp;
	str = (void *)str;

	sem_wait(philo->rules->print);
	if (!philo->rules->is_died)
	{
		time_stamp = current_time(philo->rules->start_time);
		printf("%ld %d %s\n", time_stamp, philo->id + 1, str);
	}
	sem_post(philo->rules->print);
}

void	ft_usleep(long duration)
{
	long	start;

	start = get_time();
	while (current_time(start) < duration)
		usleep(50);
}

long	get_time(void)
{
	struct timeval	tv;
	int				timestamp;

	timestamp = gettimeofday(&tv, NULL);
	if (timestamp == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (-1);
}

long	current_time(long start_time)
{
	return (get_time() - start_time);
}
