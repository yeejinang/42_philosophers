/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:00:09 by yang              #+#    #+#             */
/*   Updated: 2022/02/18 15:48:45 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# define BRED "\033[1;31m"
# define GRN "\e[0;32m"
# define BLU "\e[0;34m"
# define YEL "\e[0;33m"
# define BYEL "\e[1;33m"

# define PICK_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

typedef struct s_rules
{
	int			total_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			times_must_eat;
	long		start_time;
	pthread_mutex_t print;
	pthread_mutex_t	*fork;
}	t_rules;

typedef struct s_philo
{
	pthread_mutex_t	fork_lock;
	int			first_fork;
	int			second_fork;
	long			last_meal;
	unsigned int	count_meal;
	int				id;
	int				state;
	t_rules			*rules;
}	t_philo;

long	ft_atoi(const char *str);
long	current_time(long int start_time);
void	print_state(t_philo *philo, int state);

#endif