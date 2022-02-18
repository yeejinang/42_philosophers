/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:59:18 by yang              #+#    #+#             */
/*   Updated: 2022/02/18 16:04:51 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	starting_time(void)
{
	struct timeval	tv;
	int				timestamp;

	timestamp = gettimeofday(&tv, NULL);
	if (timestamp == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (-1);
}

long	current_time(long int start_time)
{
	struct timeval	tv;
	int				timestamp;
	long 			current_time;

	timestamp = gettimeofday(&tv, NULL);
	if (start_time != -1 && timestamp != -1)
	{
		current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		return (current_time - start_time);
	}
	return (-1);
}

void	save_info(int argc, char *argv[], t_rules *rules)
{
	int	i;

	i = -1;
	rules->total_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]) * 1000;
	rules->time_to_eat = ft_atoi(argv[3]) * 1000;
	rules->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		rules->times_must_eat = ft_atoi(argv[5]);
	else
		rules->times_must_eat = -1;
	rules->start_time = starting_time();
}

void	set_fork(t_philo *philo)
{
	int	temp;

	philo->first_fork = philo->id;
	philo->second_fork = (philo->id + 1) % (philo->rules->total_philos);
	if (philo->second_fork < philo->first_fork)
	{
		temp = philo->first_fork;
		philo->first_fork = philo->second_fork;
		philo->second_fork = temp;
		//printf("SWAP:\nphilo: %d\t first: %d\t second: %d\n", philo->id, philo->first_fork, philo->second_fork);
	}
	//printf("philo: %d\t first: %d\t second: %d\n", philo->id, philo->first_fork, philo->second_fork);
}

void	*routine(t_philo *argc)
{
	while (1)
	{
		pthread_mutex_lock(argc->rules->fork + argc->first_fork);
		print_state(argc, PICK_FORK);
		pthread_mutex_lock(argc->rules->fork + argc->second_fork);
		print_state(argc, PICK_FORK);
		//printf("Philo %d has taken a fork %d\n", argc->id, argc->second_fork);
		print_state(argc, EATING);
		//printf("Philo %d is eating\n", argc->id);
		usleep(argc->rules->time_to_eat);
		pthread_mutex_unlock(argc->rules->fork + argc->first_fork);
		//printf("Philo %d had put down the fork %d\n", argc->id, argc->first_fork);
		pthread_mutex_unlock(argc->rules->fork + argc->second_fork);
		print_state(argc, SLEEPING);
		//printf("Philo %d had put down the fork %d\n", argc->id, argc->second_fork);
		//printf("Philo %d is sleeping\n", argc->id);
		usleep(argc->rules->time_to_sleep);
		print_state(argc, THINKING);
	}
	return (NULL);
}

int main(int argc, char *argv[])
{
	if (argc == 5 || argc == 6)
	{
		t_philo	*philo[ft_atoi(argv[1])];
		t_rules	*rules;
		pthread_t	tid[ft_atoi(argv[1])];
		int			i;
		int			check;

		rules = (t_rules *)malloc(sizeof(t_rules));
		save_info(argc, argv, rules);
		rules->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
		i = -1;
		while (++i < ft_atoi(argv[1]))
		{
			//printf("philo[0]: %p\n", philo[i]);
			philo[i] = (t_philo *)malloc(sizeof(t_philo));
			philo[i]->id = i;
			philo[i]->rules = rules;
			set_fork(philo[i]);
			//printf("id: %d\n", philo[i]->id);
			pthread_mutex_init(&rules->fork[i], NULL);
			pthread_mutex_init(&rules->print, NULL);
			check = pthread_create(&tid[i], NULL, &routine, philo[i]);
			if (check != 0)
			{
				printf(BRED"Failed to create thread[%d]\n", i);
				return (1);
			}
		}
		i = 0;
		while (++i < ft_atoi(argv[1]))
		{
			check = pthread_join(tid[i], NULL);
			pthread_mutex_destroy(&rules->fork[i]);
			pthread_mutex_destroy(&rules->print);
			if (check != 0)
			{
				printf(BRED"Failed to join thread[%d]\n", i);
				return (1);
			}
		}
		/*printf("size of philo: %lu\n", sizeof(rules.philo));
		printf("size of philo: %lu\n", sizeof(rules.philo[0]));
		printf("no of philos: %d\n", rules.no_of_philos);
		printf("time to die: %ld\n", rules.time_to_die);
		printf("time to eat: %ld\n", rules.time_to_eat);
		printf("time to sleep: %ld\n", rules.time_to_sleep);*/
	}
	else
	{
		printf(BRED"Incorrect arguments.\n\n");
		printf(BYEL"Arguments have to be formatted as below:\n");
		printf(BLU"./philo [number_of_philosphers] [time_to_die] [time_to_eat] ");
		printf(BLU"[time_to_sleep] [(OPTIONAL)number_of_times_each_philosopher_must_eat]\n");
	}
	//printf("%d\n", gettimeofday(&tv, NULL));
	//printf("second: %ld\t microsecond: %d\n", tv.tv_sec, tv.tv_usec / 1000);
}