/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:02:19 by yang              #+#    #+#             */
/*   Updated: 2022/03/09 13:25:35 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pickup_fork(t_philo *philo)
{
	sem_wait(philo->rules->fork);
	print_state(philo, "has taken a fork");
	sem_wait(philo->rules->fork);
	print_state(philo, "has taken a fork");
	sem_wait(philo->rules->lock_info);
}

static void	putdown_fork(t_philo *philo)
{
	sem_post(philo->rules->fork);
	sem_post(philo->rules->fork);
}

static void	routine(void *argc)
{
	t_philo	*philo;
	pthread_t tid;

	philo = (t_philo *)argc;
	printf("debug: %d rules add: %p\t death: %d\n", philo->id, philo->rules, philo->rules->is_died);
	//pthread_create(&tid, NULL, &check_death, (void *)philo);
	if (!(philo->id % 2))
		ft_usleep(philo->rules->time_to_eat);
	pthread_create(&tid, NULL, &check_death, (void *)philo);
	//pthread_detach(tid);
	while (philo->rules->is_died != 1)
	{
		//printf("philo %d is died: %d\n", philo->id, philo->rules->is_died);
		pickup_fork(philo);
		//printf("Philo is eating\n");
		print_state(philo, "is eating");
		philo->last_meal = current_time(philo->rules->start_time);
		sem_post(philo->rules->lock_info);
		ft_usleep(philo->rules->time_to_eat);
		philo->count_meal++;
		putdown_fork(philo);
		print_state(philo, "is sleeping");
		ft_usleep(philo->rules->time_to_sleep);
		print_state(philo, "is thinking");
	}
	pthread_join(tid, NULL);
	if (philo->rules->is_died)
		exit(1);
	exit(0);
}

static int	exit_routine(t_rules *rules)
{
	int	i;
	int status;

	i = -1;
	waitpid(-1, &status, 0);
	while (status && ++i < rules->total)
		kill(rules->pid[i], SIGKILL);
	sem_close(rules->fork);
	sem_close(rules->print);
	sem_close(rules->lock_info);
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/lock_info");
	free_exit(rules);
	return (0);
}

int	philosopher(t_rules *rules)
{
	int			i;

	i = -1;
	rules->start_time = get_time();
	while (++i < rules->total)
	{
		//rules->philo[i].pid = fork();
		rules->pid[i] = fork();
		printf("i: %d parent: %d\t child: %d\n", i, getppid(), getpid());
		if (rules->pid[i] == 0)
		{
			printf("child process\n");
			//routine(&rules->philo[i]);
		}
		//if (rules->philo[i].pid == 0)
			//routine(&rules->philo[i]);
		usleep(150);
	}
	printf("HELLO\tparent: %d\t child: %d\n", getppid(), getpid());
	/*if (exit_routine(rules))
	{
		printf("Error occurred when exiting threads\n");
		free_exit(rules);
	}*/
	return (0);
}
