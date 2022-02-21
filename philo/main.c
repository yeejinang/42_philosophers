/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:59:18 by yang              #+#    #+#             */
/*   Updated: 2022/02/21 18:47:31 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	save_info(int argc, char *argv[], t_rules *rules)
{
	int	i;

	i = -1;
	rules->total_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]) * 1000;
	rules->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		rules->times_must_eat = ft_atoi(argv[5]);
	else
		rules->times_must_eat = -1;
	rules->is_died = 0;
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

/*void	*routine(void *argc)
{
	t_philo	*philo = (t_philo *)argc;

	while (philo->rules->is_dead != 1)
	{
		pthread_mutex_lock(philo->rules->fork + philo->first_fork);
		print_state(philo, PICK_FORK);
		pthread_mutex_lock(philo->rules->fork + philo->second_fork);
		print_state(philo, PICK_FORK);
		//printf("Philo %d has taken a fork %d\n", argc->id, argc->second_fork);
		print_state(philo, EATING);
		philo->count_meal++;
		//printf("Philo %d is eating\n", argc->id);
		usleep(philo->rules->time_to_eat);
		philo->last_meal = current_time(philo->rules->start_time);
		printf("last meal: %ld\n", philo->last_meal);
		pthread_mutex_unlock(philo->rules->fork + philo->first_fork);
		//printf("Philo %d had put down the fork %d\n", argc->id, argc->first_fork);
		pthread_mutex_unlock(philo->rules->fork + philo->second_fork);
		print_state(philo, SLEEPING);
		//printf("Philo %d had put down the fork %d\n", argc->id, argc->second_fork);
		//printf("Philo %d is sleeping\n", argc->id);
		usleep(philo->rules->time_to_sleep);
		print_state(philo, THINKING);
	}
	return (NULL);
}*/

int init(t_rules *rules)
{
	int	err1;
	int	err2;
	int	err3;
	int	i;

	i = -1;
	while (++i < rules->total_philos)
	{
		err1 = pthread_mutex_init(&rules->fork[i], NULL);
		if (err1 != 0)
			return (1);
	}
	err2 = pthread_mutex_init(&rules->print, NULL);
	err3 = pthread_mutex_init(&rules->death, NULL);
	if (err2 != 0 || err3 != 0)
		return (1);
	return (0);
}

int main(int argc, char *argv[])
{
	t_rules			rules;
	//pthread_t	tid[ft_atoi(argv[1])];
	t_philo			philo[ft_atoi(argv[1])];
	pthread_mutex_t	fork[ft_atoi(argv[1])];

	if (argc == 5 || argc == 6)
	{
		save_info(argc, argv, &rules);
		rules.philo = philo;
		rules.fork = fork;
		if (init(&rules))
		{
			printf("Error occurred when creating thread\n");
			return (1);
		}
		if (philo(&rules))
			return (1);
	}
}

/*int main(int argc, char *argv[])
{
	if (argc == 5 || argc == 6)
	{
		t_philo	*philo[ft_atoi(argv[1])];
		t_rules	*rules;
		pthread_t	tid[ft_atoi(argv[1])];
		pthread_t	tid_death[ft_atoi(argv[1])];
		int			i;
		int			check;
		int			check2;

		rules = (t_rules *)malloc(sizeof(t_rules));
		save_info(argc, argv, rules);
		//printf("philo in rule: %p\n", rules->philo);
		rules->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
		i = -1;
		while (++i < ft_atoi(argv[1]))
		{
			//printf("philo[0]: %p\n", philo[i]);
			philo[i] = (t_philo *)malloc(sizeof(t_philo));
			//rules->philo = philo;
			philo[i]->id = i;
			philo[i]->rules = rules;
			set_fork(philo[i]);
			//printf("id: %d\n", philo[i]->id);
			pthread_mutex_init(&rules->fork[i], NULL);
			pthread_mutex_init(&rules->print, NULL);
			pthread_mutex_init(&rules->death, NULL);
			check = pthread_create(&tid[i], NULL, routine, (void*)philo[i]);
			check2 = pthread_create(&tid_death[i], NULL, check_death, (void*)philo[i]);
			if (check != 0) //|| check2 != 0)
			{
				printf(BRED"Failed to create thread[%d]\n", i);
				return (1);
			}
		}*/
		/*check = pthread_create(&tid_death, NULL, check_death, (void*)(rules));
		if (check != 0)
		{
			printf(BRED"Failed to create thread[%d]\n", i);
			return (1);
		}*/
		/*i = 0;
		while (++i < ft_atoi(argv[1]))
		{
			check = pthread_join(tid[i], NULL);
			pthread_mutex_destroy(&rules->fork[i]);
			pthread_mutex_destroy(&rules->print);
			pthread_mutex_destroy(&rules->death);
			if (check != 0)
			{
				printf(BRED"Failed to join thread[%d]\n", i);
				return (1);
			}
		}*/
		//pthread_join(tid_death, NULL);
		/*printf("size of philo: %lu\n", sizeof(rules.philo));
		printf("size of philo: %lu\n", sizeof(rules.philo[0]));
		printf("no of philos: %d\n", rules.no_of_philos);
		printf("time to die: %ld\n", rules.time_to_die);
		printf("time to eat: %ld\n", rules.time_to_eat);
		printf("time to sleep: %ld\n", rules.time_to_sleep);*/
	/*}
	else
	{
		printf(BRED"Incorrect arguments.\n\n");
		printf(BYEL"Arguments have to be formatted as below:\n");
		printf(BLU"./philo [number_of_philosphers] [time_to_die] [time_to_eat] ");
		printf(BLU"[time_to_sleep] [(OPTIONAL)number_of_times_each_philosopher_must_eat]\n");
	}
	//printf("%d\n", gettimeofday(&tv, NULL));
	//printf("second: %ld\t microsecond: %d\n", tv.tv_sec, tv.tv_usec / 1000);
}*/