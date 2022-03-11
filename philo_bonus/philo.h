/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:00:09 by yang              #+#    #+#             */
/*   Updated: 2022/03/11 16:29:51 by yang             ###   ########.fr       */
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
# include <signal.h>

# define BRED "\033[1;31m"
# define GRN "\e[0;32m"
# define BLU "\e[0;34m"
# define YEL "\e[0;33m"
# define BYEL "\e[1;33m"

typedef struct s_info
{
	struct s_philo	*philo;
	int				total;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				times_must_eat;
	int				is_died;
	sem_t			*print;
	sem_t			*lock_info;
	sem_t			*fork;
	sem_t			*death;
	sem_t			*lock_meal;
	pid_t			*pid;
}	t_info;

typedef struct s_philo
{
	long			last_meal;
	int				id;
	int				first_fork;
	int				second_fork;
	int				count_meal;
	t_info			*info;
}	t_philo;

/* ------------ parsing info --------------- */
int		check_arg(char *argv[]);
long	ft_atoi(const char *str);
int		init(int argc, char *argv[], t_info *info);
/* ------------ get time in microsecond ------------ */
long	get_time(void);
long	current_time(long int start_time);
/* ------------ routine for each threads ----------- */
int		philosopher(t_info *info);
void	*check_meal(void *argc);
/* ------------ utils for philo ---------------- */
void	print_state(t_philo *philo, char *str);
void	*check_death(void *argc);
void	ft_usleep(long duration);
void	free_exit(t_info *info);

#endif
