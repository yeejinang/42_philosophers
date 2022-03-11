/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:34:40 by yang              #+#    #+#             */
/*   Updated: 2022/03/11 16:28:18 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	}
	if (info->times_must_eat != -1)
	{
		sem_post(info->death);
	}
	return (argc);
}

void	print_state(t_philo *philo, char *str)
{
	long	time_stamp;

	sem_wait(philo->info->print);
	if (!philo->info->is_died)
	{
		time_stamp = current_time(philo->info->start_time);
		printf("%ld %d %s\n", time_stamp, philo->id + 1, str);
	}
	sem_post(philo->info->print);
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
