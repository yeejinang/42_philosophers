/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:02:19 by yang              #+#    #+#             */
/*   Updated: 2022/03/10 16:58:20 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pickup_fork(t_philo *philo)
{
	sem_wait(philo->info->fork);
	print_state(philo, "has taken a fork");
	sem_wait(philo->info->fork);
	print_state(philo, "has taken a fork");
	sem_wait(philo->info->lock_info);
	print_state(philo, "is eating");
	philo->last_meal = current_time(philo->info->start_time);
	sem_post(philo->info->lock_info);
	ft_usleep(philo->info->time_to_eat);
	philo->count_meal++;
}

static void	putdown_fork(t_philo *philo)
{
	sem_post(philo->info->fork);
	sem_post(philo->info->fork);
}

static int	routine(void *argc)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)argc;
	if (!(philo->id % 2))
		ft_usleep(philo->info->time_to_eat);
	if (pthread_create(&tid, NULL, &check_death, (void *)philo))
		return (1);
	while (philo->info->is_died != 1)
	{
		pickup_fork(philo);
		putdown_fork(philo);
		if (philo->count_meal == philo->info->times_must_eat)
			break ;
		print_state(philo, "is sleeping");
		ft_usleep(philo->info->time_to_sleep);
		print_state(philo, "is thinking");
	}
	if (pthread_join(tid, NULL))
		return (1);
	exit(1);
}

static int	exit_routine(t_info *info)
{
	int	i;
	int	status;

	i = -1;
	waitpid(-1, &status, 0);
	while (status && ++i < info->total)
		kill(info->pid[i], SIGKILL);
	if (sem_close(info->fork) || sem_unlink("/fork")
		|| sem_close(info->print) || sem_unlink("/print")
		|| sem_close(info->lock_info) || sem_unlink("/lock_info"))
		return (1);
	free_exit(info);
	return (0);
}

int	philosopher(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = get_time();
	while (++i < info->total)
	{
		info->pid[i] = fork();
		if (info->pid[i] == -1)
			exit(1);
		if (info->pid[i] == 0)
		{
			if (routine(&info->philo[i]))
				printf(BRED"Error occurred when creating thread\n");
		}
		usleep(250);
	}
	if (exit_routine(info))
	{
		printf(BRED"Error occurred when exiting threads\n");
		free_exit(info);
	}
	return (0);
}
