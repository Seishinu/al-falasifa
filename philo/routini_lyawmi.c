/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routini_lyawmi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:43:03 by ynuiga            #+#    #+#             */
/*   Updated: 2022/05/14 17:16:55 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	activity(int num, t_philo philosophers)
{
	int	i;

	i = 0;
	if (philosophers.info->philo_stat == 0)
		return ;
	else if (num == PHF)
		printf("%ldms\t%d has taken a fork\n",
			current_time_ms() - philosophers.info->starting_time,
			philosophers.philo_id);
	else if (num == PIE)
	{
		printf("%ldms\t%d is eating\n",
			current_time_ms() - philosophers.info->starting_time,
			philosophers.philo_id);
		i++;
	}
	else if (num == PIS)
		printf("%ldms\t%d is sleeping\n",
			current_time_ms() - philosophers.info->starting_time,
			philosophers.philo_id);
	else if (num == PIT)
		printf("%ldms\t%d is thinking\n",
			current_time_ms() - philosophers.info->starting_time,
			philosophers.philo_id);
}

int	less_eating_philosopher(t_philo	*philosophers)
{
	int	i;
	int	min;

	i = 1;
	min = philosophers[0].philo_times_ate;
	if (philosophers->info->number_of_philos < 3)
	{
		if (min > philosophers[1].philo_times_ate)
			min = philosophers[1].philo_times_ate;
	}
	else
	{
		while (i < philosophers->info->number_of_philos)
		{
			if (min > philosophers[i].philo_times_ate)
				min = philosophers[i].philo_times_ate;
			i++;
		}
	}
	if (min >= philosophers->info->number_of_meals)
		return (0);
	return (1);
}

void	philo_survival(t_philo	*philosophers)
{
	int		i;
	long	difference;

	i = 0;
	while (1)
	{
		if (i == philosophers->info->number_of_philos)
			i = 0;
		difference = current_time_ms() - philosophers->last_meal;
		if (philosophers[i].info->time_to_die <= difference
			|| !less_eating_philosopher(philosophers))
		{
			if (philosophers->info->number_of_meals != -1
				&& !less_eating_philosopher(philosophers))
			{
				printf("Everyone ate atleast the number of meals they need\n");
				exit (0);
			}
			else
			{
				philosophers->info->philo_stat = 0;
				printf("i is = %d\n", i);
				printf("%ldms\t%d is DEAD!\n",
					current_time_ms() - philosophers[i].info->starting_time,
					philosophers[i].philo_id);
				exit (0);
			}
		}
		i++;
	}
}

void	*routine(void	*param)
{
	t_philo	*philosophers;
	long	time_right_now;
	long	i;

	i = 0;
	philosophers = (t_philo *)param;
	while (philosophers->info->philo_stat)
	{
		pthread_mutex_lock(&philosophers
			->info->forks[philosophers->philo_id - 1]);
		activity(PHF, *philosophers);
		pthread_mutex_lock(&philosophers->info->forks[philosophers->philo_id
			% philosophers->info->number_of_philos]);
		activity(PHF, *philosophers);
		philosophers->philo_times_ate++;
		activity(PIE, *philosophers);
		time_right_now = current_time_ms();
		philosophers->last_meal = current_time_ms();
		while (current_time_ms() - time_right_now
			< philosophers->info->time_to_eat)
			usleep(50);
		pthread_mutex_unlock(&philosophers->info
			->forks[philosophers->philo_id - 1]);
		pthread_mutex_unlock(&philosophers->info->forks[philosophers->philo_id
			% philosophers->info->number_of_philos]);
		activity(PIS, *philosophers);
		time_right_now = current_time_ms();
		while (current_time_ms() - time_right_now
			< philosophers->info->time_to_sleep)
			usleep(50);
		activity(PIT, *philosophers);
		i++;
	}
	return (NULL);
}
