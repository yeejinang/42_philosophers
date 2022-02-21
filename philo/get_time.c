/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:35:16 by yang              #+#    #+#             */
/*   Updated: 2022/02/21 14:35:37 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	starting_time(void)
{
	struct timeval	tv;
	int				timestamp;

	timestamp = gettimeofday(&tv, NULL);
	if (timestamp == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (-1);
}

long	current_time(long int start_time)
{
	struct timeval	tv;
	int				timestamp;
	long 			current_time;

	timestamp = gettimeofday(&tv, NULL);
	if (start_time != -1 && timestamp != -1)
	{
		current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		return (current_time - start_time);
	}
	return (-1);
}
