/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:34:40 by yang              #+#    #+#             */
/*   Updated: 2022/03/07 15:21:24 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_rules *rules)
{
	int		i;
	long	last_meal;
	long	last;

	while (rules->is_died != 1)
	{
		i = -1;
		while (++i < rules->total)
		{
			pthread_mutex_lock(&rules->lock_info);
			last = rules->philo[i].last_meal;
			last_meal = current_time(rules->start_time) - last;
			if (last_meal > rules->time_to_die || (rules->times_must_eat != -1
					&& rules->philo[i].count_meal == rules->times_must_eat))
			{
				if (last_meal > rules->time_to_die)
					print_state(&rules->philo[i], "died");
				rules->is_died = 1;
				pthread_mutex_unlock(&rules->lock_info);
				break ;
			}
			pthread_mutex_unlock(&rules->lock_info);
		}
		usleep(500);
	}
}

void	print_state(t_philo *philo, char *str)
{
	long	time_stamp;

	pthread_mutex_lock(&philo->rules->print);
	if (!philo->rules->is_died)
	{
		time_stamp = current_time(philo->rules->start_time);
		printf("%ld %d %s\n", time_stamp, philo->id + 1, str);
	}
	pthread_mutex_unlock(&philo->rules->print);
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
