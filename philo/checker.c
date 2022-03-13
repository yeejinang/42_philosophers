/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:46:47 by yang              #+#    #+#             */
/*   Updated: 2022/03/12 13:22:19 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_info *info)
{
	int		i;
	long	last_meal;
	long	last;

	while (!info->end)
	{
		i = -1;
		while (++i < info->total && !info->is_died)
		{
			pthread_mutex_lock(&info->lock_info);
			last = info->philo[i].last_meal;
			last_meal = current_time(info->start_time) - last;
			if (last_meal > info->time_to_die && !info->philo[i].done)
			{
				print_state(&info->philo[i], "died");
				info->is_died = 1;
				info->end = 1;
				if (info->total == 1)
					pthread_mutex_unlock(&info->fork[i]);
				pthread_mutex_unlock(&info->lock_info);
				break ;
			}
			pthread_mutex_unlock(&info->lock_info);
		}
		usleep(500);
	}
}

int	check_meal(t_philo *philo, t_info *info)
{
	if (info->times_must_eat != -1)
	{
		if (philo->count_meal == info->times_must_eat)
		{
			info->done_eat++;
			philo->done = 1;
		}
	}
	if (info->done_eat == info->total)
	{
		info->end = 1;
		printf(BLU"Philosophers have eaten %d times.\n", info->times_must_eat);
		return (1);
	}
	return (0);
}
