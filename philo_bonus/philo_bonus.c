/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:20:23 by ynuiga            #+#    #+#             */
/*   Updated: 2022/05/16 20:55:04 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int static	quickmaphs(const char *str, int sign, size_t i)
{
	size_t	rslt;

	rslt = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		if ((unsigned long)rslt * 10 + (str[i] - 48)
			> 2147483647 && sign == 1)
			return (0);
		else if ((unsigned long)rslt * 10 + (str[i] - 48)
			> (unsigned long)9223372036854775807 + 1 && sign == -1)
			return (0);
		rslt = (rslt * 10) + (str[i] - 48);
		i++;
	}
	return (rslt * sign);
}

int	ft_atoi(const char	*str)
{
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (quickmaphs(str, sign, i));
}

void	*philo_survival(void	*param)
{
	t_philo	*philosophers;
	long	difference;

	philosophers = (t_philo *)param;
	while (1)
	{
		difference = current_time_ms() - philosophers->last_meal;
		if (philosophers->info->time_to_die <= difference
			|| philosophers->info->philo_times_ate
			>= philosophers->info->number_of_meals)
		{
			if (philosophers->info->time_to_die <= difference)
			{
				sem_wait(philosophers->semaprint);
				printf("%ldms\t%d is DEAD!\n",
					current_time_ms() - philosophers->info->starting_time,
					philosophers->philo_id);
			}
			else
			{
				sem_wait(philosophers->semaprint);
				printf("meals %ld, times at %ld\n", philosophers->info->number_of_meals, philosophers->info->philo_times_ate);
				printf("ALL PHILOSOPHERS ATE ALL THEIR MEALS\n");
				exit (1);
			}
			exit (0);
		}
	}
	return (0);
}

void	activity(int	action, t_philo	*philosophers)
{
	if (action == PHF)
	{
		sem_wait(philosophers->semaprint);
		printf("%ldms\t%d has taken a fork\n",
			current_time_ms() - philosophers->info->starting_time,
			philosophers->philo_id);
		sem_post(philosophers->semaprint);
	}
	else if (action == PIE)
	{
		sem_wait(philosophers->semaprint);
		printf("%ldms\t%d is eating\n",
			current_time_ms() - philosophers->info->starting_time,
			philosophers->philo_id);
		sem_post(philosophers->semaprint);
	}
	else if (action == PIS)
	{
		sem_wait(philosophers->semaprint);
		printf("%ldms\t%d is sleeping\n",
			current_time_ms() - philosophers->info->starting_time,
			philosophers->philo_id);
		sem_post(philosophers->semaprint);
	}
	else if (action == PIT)
	{
		sem_wait(philosophers->semaprint);
		printf("%ldms\t%d is thinking\n",
			current_time_ms() - philosophers->info->starting_time,
			philosophers->philo_id);
		sem_post(philosophers->semaprint);
	}
}

void	*routine(sem_t	*semaphilo, t_philo	*philosophers)
{
	long	time_right_now;

	pthread_create(&philosophers->philo, NULL,
		&philo_survival, philosophers);
	while (1)
	{
		sem_wait(semaphilo);
		activity(PHF, philosophers);
		sem_wait(semaphilo);
		activity(PHF, philosophers);
		philosophers->info->philo_times_ate++;
		activity(PIE, philosophers);
		time_right_now = current_time_ms();
		philosophers->last_meal = current_time_ms();
		while (current_time_ms() - time_right_now
			< philosophers->info->time_to_eat)
			usleep(50);
		sem_post(semaphilo);
		sem_post(semaphilo);
		activity(PIS, philosophers);
		time_right_now = current_time_ms();
		while (current_time_ms() - time_right_now
			< philosophers->info->time_to_sleep)
			usleep(50);
		activity(PIT, philosophers);
	}
	return (0);
}

int	main(int	argc, char	**argv)
{
	t_philo	*philosophers;
	t_info	info;
	sem_t	*semaphilo;
	sem_t	semaprint;
	int		exit_code;
	int		i;

	error_checking_b(argc, argv);
	philosophers = malloc(sizeof(t_philo));
	info.number_of_philos = ft_atoi(argv[1]);
	info.time_to_die = ft_atoi(argv[2]);
	info.time_to_eat = ft_atoi(argv[3]);
	info.time_to_sleep = ft_atoi(argv[4]);
	philosophers->philo_pid = (pid_t *)malloc(sizeof(pid_t)
		* (info.number_of_philos + 1));
	philosophers->philo_pid[info.number_of_philos] = 0;
	if (argc == 6)
		info.number_of_meals = ft_atoi(argv[5]);
	sem_unlink("semaphilos");
	semaphilo = sem_open("semaphilos", O_CREAT, 0644, info.number_of_philos);
	philosophers->semaprint = &semaprint;
	sem_unlink("semaprint");
	philosophers->semaprint = sem_open("semaprint", O_CREAT, 0666, 1);
	philosophers->info = &info;
	info.philo_times_ate = 0;
	philosophers->info->starting_time = current_time_ms();
	i = 0;
	while (i < info.number_of_philos)
	{
		philosophers->philo_pid[i] = fork();
		if (philosophers->philo_pid[i] == -1)
			exit (1);
		else if(philosophers->philo_pid[i] == 0)
		{
			philosophers->philo_id = i + 1;
			philosophers->last_meal = philosophers->info->starting_time;
			routine(semaphilo, philosophers);
		}
		i++;
	}
	i = 0;
	while (wait(&exit_code) != -1)
	{
		if (!exit_code)
		{
			while (philosophers->philo_pid[i])
			{
				kill(philosophers->philo_pid[i], SIGKILL);
				i++;
			}
		}
	}
	return (0);
}
