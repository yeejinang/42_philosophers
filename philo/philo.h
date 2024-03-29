/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:00:09 by yang              #+#    #+#             */
/*   Updated: 2022/03/12 13:31:05 by yang             ###   ########.fr       */
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

typedef struct s_info
{
	struct s_philo	*philo;
	int				total;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				times_must_eat;
	long			start_time;
	int				is_died;
	int				end;
	int				done_eat;
	pthread_mutex_t print;
	pthread_mutex_t	lock_info;
	pthread_mutex_t	*fork;
	pthread_t		*tid;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				first_fork;
	int				second_fork;
	long			last_meal;
	int				count_meal;
	int				done;
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
/* ------------ checker if simulations need to be stop -----------*/
void	check_death(t_info *info);
int		check_meal(t_philo *philo, t_info *info);
/* ------------ utils for philo ---------------- */
void	print_state(t_philo *philo, char *str);
void	ft_usleep(long duration);
void	free_exit(t_info *info);

#endif
