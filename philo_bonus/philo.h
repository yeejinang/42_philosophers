/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:00:09 by yang              #+#    #+#             */
/*   Updated: 2022/03/07 15:27:28 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# define BRED "\033[1;31m"
# define GRN "\e[0;32m"
# define BLU "\e[0;34m"
# define YEL "\e[0;33m"
# define BYEL "\e[1;33m"

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
	sem_t 			print;
	sem_t			lock_info;
	sem_t			fork;
	pid_t			*pid;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				first_fork;
	int				second_fork;
	long			last_meal;
	int				count_meal;
	t_rules			*rules;
}	t_philo;

/* ------------ parsing info --------------- */
int		check_arg(char *argv[]);
long	ft_atoi(const char *str);
int		init(int argc, char *argv[], t_rules *rules);
/* ------------ get time in microsecond ------------ */
long	get_time(void);
long	current_time(long int start_time);
/* ------------ routine for each threads ----------- */
int		philosopher(t_rules *rules);
/* ------------ utils for philo ---------------- */
void	print_state(t_philo *philo, char *str);
void	check_death(t_rules *rules);
void	ft_usleep(long duration);
void	free_exit(t_rules *rules);

#endif
