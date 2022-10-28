/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:20:23 by ynuiga            #+#    #+#             */
/*   Updated: 2022/10/28 14:42:30 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(t_philo	*philosophers)
{
	long	time_right_now;

	pthread_create(&philosophers->philo, NULL,
		&philo_survival, philosophers);
	while (1)
	{
		prep_to_eat(philosophers);
		time_right_now = current_time_ms();
		food_activity(PIE, philosophers);
		meals(philosophers, 10);
		while (current_time_ms() - time_right_now
			< philosophers->time_to_eat)
			usleep(100);
		sem_post(philosophers->forks);
		sem_post(philosophers->forks);
		if (philosophers->number_of_meals >= 0)
			meals(philosophers, 11);
		time_right_now = current_time_ms();
		other_activities(PIS, philosophers);
		while (current_time_ms() - time_right_now
			< philosophers->time_to_sleep)
			usleep(100);
		other_activities(PIT, philosophers);
	}
	return (0);
}

void	creating_philosophers(t_philo	*philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers->number_of_philos)
	{
		philosophers->philo_pid[i] = fork();
		if (philosophers->philo_pid[i] == -1)
			exit (1);
		else if (philosophers->philo_pid[i] == 0)
		{
			philosophers->philo_id = i + 1;
			philosophers->last_meal = philosophers->starting_time;
			routine(philosophers);
		}
		usleep(50);
		i++;
	}
}

void	setting_struct(t_philo *philosophers, int argc, char **argv)
{
	philosophers->number_of_philos = ft_atoi(argv[1]);
	philosophers->time_to_die = ft_atoi(argv[2]);
	philosophers->time_to_eat = ft_atoi(argv[3]);
	philosophers->time_to_sleep = ft_atoi(argv[4]);
	philosophers->philo_pid = (pid_t *)malloc(sizeof(pid_t)
			* philosophers->number_of_philos);
	philosophers->number_of_meals = -1;
	if (argc == 6)
		philosophers->number_of_meals = ft_atoi(argv[5]);
	sem_unlink("forks");
	philosophers->forks
		= sem_open("forks", O_CREAT, 0666, philosophers->number_of_philos);
	sem_unlink("semaprint");
	sem_unlink("last_meal");
	sem_unlink("times_ate");
	philosophers->semaprint = sem_open("semaprint", O_CREAT, 0644, 1);
	philosophers->philo_times_ate = 0;
	philosophers->starting_time = current_time_ms();
	creating_philosophers(philosophers);
}

void	proc_kill(t_philo *philosophers)
{
	int	i;

	i = 0;
	while (philosophers->philo_pid[i])
	{
		kill(philosophers->philo_pid[i], SIGKILL);
		i++;
	}
}

int	main(int argc, char	**argv)
{
	t_philo	*philosophers;
	int		exit_code;
	int		times;

	error_checking_b(argc, argv);
	philosophers = malloc(sizeof(t_philo));
	setting_struct(philosophers, argc, argv);
	times = 0;
	while (waitpid(-1, &exit_code, 0) != -1)
	{
		if (!exit_code)
		{
			proc_kill(philosophers);
			return (0);
		}
		times++;
		if (times == philosophers->number_of_philos)
		{
			sem_wait(philosophers->semaprint);
			return (0);
		}
	}
	return (0);
}
