/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:34:40 by yang              #+#    #+#             */
/*   Updated: 2022/02/18 15:50:51 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, int state)
{
	char			*str[5];

	str[PICK_FORK] = "has taken a fork";
	str[EATING] = "is eating";
	str[SLEEPING] = "is sleeping";
	str[THINKING] = "is thinking";
	str[DIED] = "died\n"; 
	pthread_mutex_lock(&philo->rules->print);
	printf("%ld\tphilo %d is %s\n", current_time(philo->rules->start_time), philo->id, str[state]);
	pthread_mutex_unlock(&philo->rules->print);
}