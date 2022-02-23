/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:00:09 by yang              #+#    #+#             */
/*   Updated: 2022/02/23 10:24:58 by yang             ###   ########.fr       */
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
# define HUNGRY 5

typedef struct s_rules
{
	struct s_philo	*philo;
	int				total;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				times_must_eat;
	long			start_time;
	int				is_died;
	pthread_mutex_t print;
	pthread_mutex_t	death;
	pthread_mutex_t	lock;
	pthread_mutex_t	*fork;
	pthread_t		*tid;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				first_fork;
	int				second_fork;
	long			last_meal;
	int				count_meal;
	int				state;
	t_rules			*rules;
}	t_philo;

int	check_arg(char *argv[]);
long	get_time(void);
long	current_time(long int start_time);
long	ft_atoi(const char *str);
long	current_time(long int start_time);
void	print_state(t_philo *philo, int state);
int		is_dead(t_philo *philo);
void	*check_death(t_rules *rules);
int	philosopher(t_rules *rules);
void	*routine(void *argc);
void	pickup_fork(t_philo *philo);
void	putdown_fork(t_philo *philo);
void	set_fork(t_rules *rules, t_philo *philo);
void	ft_usleep(long duration);

#endif