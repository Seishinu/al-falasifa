/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routini_lyawmi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:43:03 by ynuiga            #+#    #+#             */
/*   Updated: 2022/05/16 11:57:42 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	activity(int action, t_philo philosophers)
{
	if (philosophers.info->philo_stat == 0)
		return ;
	else if (action == PHF)
		printf("%ldms\t%d has taken a fork\n",
			current_time_ms() - philosophers.info->starting_time,
			philosophers.philo_id);
	else if (action == PIE)
	{
		printf("%ldms\t%d is eating\n",
			current_time_ms() - philosophers.info->starting_time,
			philosophers.philo_id);
	}
	else if (action == PIS)
		printf("%ldms\t%d is sleeping\n",
			current_time_ms() - philosophers.info->starting_time,
			philosophers.philo_id);
	else if (action == PIT)
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
	while (i < philosophers->info->number_of_philos)
	{
		if (min > philosophers[i].philo_times_ate)
			min = philosophers[i].philo_times_ate;
		i++;
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
			else if (philosophers[i].info->time_to_die <= difference)
			{
				philosophers->info->philo_stat = 0;
				printf("the time diff is %ld and i is %d\n", difference, i);
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
		time_right_now = current_time_ms();
		activity(PIS, *philosophers);
		while (current_time_ms() - time_right_now
			< philosophers->info->time_to_sleep)
			usleep(50);
		activity(PIT, *philosophers);
	}
	return (0);
}
