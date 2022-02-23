/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:34:40 by yang              #+#    #+#             */
/*   Updated: 2022/02/23 10:52:29 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(t_rules *rules)
{
	int		i;
	long	last_meal;

	while (rules->is_died != 1)
	{
		i = -1;
		while (++i < rules->total)
		{
			pthread_mutex_lock(&rules->death);
			last_meal = current_time(rules->start_time) - rules->philo[i].last_meal;
			if (last_meal > rules->time_to_die || (rules->times_must_eat != -1
				&& rules->philo[i].count_meal == rules->times_must_eat))
			{
				if (last_meal > rules->time_to_die)
					print_state(&rules->philo[i], DIED);
				rules->is_died = 1;
				break;
			}
			pthread_mutex_unlock(&rules->death);
			usleep(500);
		}
	}
	return (NULL);
}

void	print_state(t_philo *philo, int state)
{
	char			*str[5];

	str[PICK_FORK] = "has taken a fork";
	str[EATING] = "is eating";
	str[SLEEPING] = "is sleeping";
	str[THINKING] = "is thinking";
	str[DIED] = "died"; 
	pthread_mutex_lock(&philo->rules->print);
	if (!philo->rules->is_died)
		printf("%ld %d %s\n", current_time(philo->rules->start_time), philo->id + 1, str[state]);
	pthread_mutex_unlock(&philo->rules->print);
}

void	ft_usleep(long duration)
{
	//long	duration;
	long	start;

	start = get_time();
	while (current_time(start) < duration)
		usleep(50);
}
