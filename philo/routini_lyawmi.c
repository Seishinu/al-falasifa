/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routini_lyawmi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:43:03 by ynuiga            #+#    #+#             */
/*   Updated: 2022/10/18 10:56:50 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	activity(int action, t_philo *philosophers)
{
	pthread_mutex_lock(philosophers->info->philo_stat_mut);
	if (philosophers->info->philo_stat == 0)
	{
		pthread_mutex_unlock(philosophers->info->philo_stat_mut);
		return ;
	}
	pthread_mutex_unlock(philosophers->info->philo_stat_mut);
	if (action == PHF)
		printf("%ld\t%d has taken a fork\n",
			current_time_ms() - philosophers->info->starting_time,
			philosophers->philo_id);
	else if (action == PIE)
	{
		printf("%ld\t%d is eating\n",
			current_time_ms() - philosophers->info->starting_time,
			philosophers->philo_id);
	}
	else if (action == PIS)
		printf("%ld\t%d is sleeping\n",
			current_time_ms() - philosophers->info->starting_time,
			philosophers->philo_id);
	else if (action == PIT)
		printf("%ld\t%d is thinking\n",
			current_time_ms() - philosophers->info->starting_time,
			philosophers->philo_id);
}

int	less_eating_philosopher(t_philo	*philosophers)
{
	int	i;
	int	min;

	if (philosophers->info->number_of_meals == -1)
		return (1);
	pthread_mutex_lock(&philosophers->info->philo_times_ate_mut[0]);
	min = philosophers[0].philo_times_ate;
	pthread_mutex_unlock(&philosophers->info->philo_times_ate_mut[0]);
	i = 1;
	while (i < philosophers->info->number_of_philos)
	{
		pthread_mutex_lock(&philosophers->info->philo_times_ate_mut[i]);
		if (min > philosophers[i].philo_times_ate)
			min = philosophers[i].philo_times_ate;
		pthread_mutex_unlock(&philosophers->info->philo_times_ate_mut[i]);
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
		pthread_mutex_lock(&philosophers->info->last_meal_mut[i]);
		difference = current_time_ms() - philosophers[i].last_meal;
		pthread_mutex_unlock(&philosophers->info->last_meal_mut[i]);
		if (philosophers->info->time_to_die <= difference
			|| !less_eating_philosopher(philosophers))
		{
			dead_end(philosophers, difference, i);
			break ;
		}
		i++;
	}
}

void	forks_down(t_philo	*philosophers)
{
	pthread_mutex_unlock(&philosophers->info
		->forks[philosophers->philo_id - 1]);
	pthread_mutex_unlock(&philosophers->info->forks[philosophers->philo_id
		% philosophers->info->number_of_philos]);
}

void	*routine(void	*param)
{
	t_philo	*philosophers;
	long	time_right_now;

	philosophers = (t_philo *)param;
	pthread_mutex_lock(philosophers->info->philo_stat_mut);
	while (philosophers->info->philo_stat)
	{
		pthread_mutex_unlock(philosophers->info->philo_stat_mut);
		food_time(philosophers);
		time_right_now = current_time_ms();
		while (current_time_ms() - time_right_now
			< philosophers->info->time_to_eat)
			usleep(50);
		forks_down(philosophers);
		activity(PIS, philosophers);
		time_right_now = current_time_ms();
		while (current_time_ms() - time_right_now
			< philosophers->info->time_to_sleep)
			usleep(50);
		activity(PIT, philosophers);
		pthread_mutex_lock(philosophers->info->philo_stat_mut);
	}
	pthread_mutex_unlock(philosophers->info->philo_stat_mut);
	return (0);
}
