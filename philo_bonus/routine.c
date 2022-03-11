/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:02:19 by yang              #+#    #+#             */
/*   Updated: 2022/03/11 16:28:30 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *argc)
{
	long	last_meal;
	t_philo	*philo;

	philo = (t_philo *)argc;
	while (1)
	{
		sem_wait(philo->info->lock_info);
		last_meal = current_time(philo->info->start_time) - philo->last_meal;
		if (last_meal > philo->info->time_to_die)
		{
			print_state(philo, "died");
			sem_post(philo->info->death);
			sem_post(philo->info->lock_info);
			exit(0);
		}
		sem_post(philo->info->lock_info);
		usleep (200);
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo)
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
	pthread_detach(tid);
	while (philo->count_meal != philo->info->times_must_eat)
	{
		philo_eat(philo);
		if (philo->count_meal == philo->info->times_must_eat)
		{
			sem_post(philo->info->lock_meal);
			break ;
		}
		print_state(philo, "is sleeping");
		ft_usleep(philo->info->time_to_sleep);
		print_state(philo, "is thinking");
	}
	exit(0);
}

static int	exit_routine(t_info *info)
{
	int	i;
	int	status;

	i = -1;
	sem_wait(info->death);
	while (++i < info->total)
	{
		if (info->times_must_eat != -1
			&& info->philo[i].count_meal < info->times_must_eat)
		{
			sem_post(info->lock_meal);
			info->philo[i].count_meal = info->times_must_eat;
		}
		kill(info->pid[i], SIGKILL);
	}
	if (sem_close(info->fork) || sem_unlink("/fork")
		|| sem_close(info->print) || sem_unlink("/print")
		|| sem_close(info->lock_info) || sem_unlink("/lock_info")
		|| sem_close(info->death) || sem_unlink("/death")
		|| sem_close(info->lock_meal) || sem_unlink("/lock_meal"))
		return (1);
	free_exit(info);
	return (0);
}

int	philosopher(t_info *info)
{
	int			i;
	pthread_t	tid;

	i = -1;
	info->start_time = get_time();
	pthread_create(&tid, NULL, &check_meal, (void *)info);
	pthread_detach(tid);
	while (++i < info->total)
	{
		info->pid[i] = fork();
		if (info->pid[i] == -1)
			exit(1);
		if (!info->pid[i])
		{
			if (routine(&info->philo[i]))
				printf(BRED"Error occurred when creating thread\n");
		}
		usleep(300);
	}
	if (exit_routine(info))
	{
		printf(BRED"Error occurred when exiting threads\n");
		free_exit(info);
	}
	return (0);
}
