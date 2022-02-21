/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:34:40 by yang              #+#    #+#             */
/*   Updated: 2022/02/21 18:55:42 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int		is_died(t_rules *rules, t_philo *philo)
{
	printf("time to die: %ld\t last_meal: %ld\n", rules->time_to_die, philo->last_meal);
	if (current_time(rules->start_time) - philo->last_meal > rules->time_to_die)
	{
		printf("is dead\n");
		rules->is_dead = 1;
		print_state(philo, DIED);
		return (1);
	}
	return (0);
}*/

void	*check_death(void *argc)
{
	t_philo	*philo;
	t_rules	*rules;
	long	last_meal;

	philo = (t_philo*)argc;
	rules = philo->rules;
	while (rules->is_died != 1)
	{
		//pthread_mutex_lock(&rules->death);
		last_meal = current_time(rules->start_time) - philo->last_meal;
		if (last_meal > rules->time_to_die)
		{
			rules->is_died = 1;
			print_state(philo, DIED);
		}
		//pthread_mutex_unlock(&rules->death);
		usleep(5000);
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
	str[DIED] = "died\n"; 
	pthread_mutex_lock(&philo->rules->print);
	printf("%ld\tphilosopher %d %s\n", current_time(philo->rules->start_time), philo->id, str[state]);
	pthread_mutex_unlock(&philo->rules->print);
}