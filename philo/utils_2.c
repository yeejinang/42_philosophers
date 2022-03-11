/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:34:40 by yang              #+#    #+#             */
/*   Updated: 2022/03/11 19:30:11 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_info *info)
{
	int		i;
	//int		philo_done;
	long	last_meal;
	long	last;

	//philo_eat = 0;
	while (!info->is_died && info->done_eat != info->total)
	{
		i = -1;
		while (++i < info->total)
		{
			pthread_mutex_lock(&info->lock_info);
			last = info->philo[i].last_meal;
			last_meal = current_time(info->start_time) - last;
			if (last_meal > info->time_to_die || info->done_eat == info->total)
			{
				if (last_meal > info->time_to_die && info->philo[i].count_meal < info->times_must_eat)
					print_state(&info->philo[i], "died");
				info->is_died = 1;
				pthread_mutex_unlock(&info->lock_info);
				break ;
			}
			pthread_mutex_unlock(&info->lock_info);
		}
		//printf("checking death\n");
		usleep(500);
	}
	//return (NULL);
	//exit(0);
}

void	print_state(t_philo *philo, char *str)
{
	long	time_stamp;

	pthread_mutex_lock(&philo->info->print);
	if (!philo->info->is_died)
	{
		time_stamp = current_time(philo->info->start_time);
		printf("%ld %d %s\n", time_stamp, philo->id + 1, str);
	}
	pthread_mutex_unlock(&philo->info->print);
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
	if (!timestamp)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (-1);
}

long	current_time(long start_time)
{
	return (get_time() - start_time);
}
