/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:23:56 by ynuiga            #+#    #+#             */
/*   Updated: 2022/10/18 10:53:46 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	mutex_destroyer(t_philo	*philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers->info->number_of_philos)
	{
		pthread_mutex_destroy(&philosophers->info->forks[i]);
		pthread_mutex_destroy(&philosophers->info->last_meal_mut[i]);
		pthread_mutex_destroy(&philosophers->info->philo_times_ate_mut[i]);
		i++;
	}
	pthread_mutex_destroy(philosophers->info->philo_stat_mut);
}

void	dead_end(t_philo *philosophers, long difference, int i)
{
	pthread_mutex_lock(philosophers->info->philo_stat_mut);
	philosophers->info->philo_stat = 0;
	pthread_mutex_unlock(philosophers->info->philo_stat_mut);
	if (philosophers->info->time_to_die <= difference)
	{
		printf("%ldms\t%d died\n",
			current_time_ms() - philosophers[i].info->starting_time,
			philosophers[i].philo_id);
	}
	else
		printf("Everyone ate atleast the number of meals they need\n");
}

void	food_time(t_philo	*philosophers)
{
	pthread_mutex_lock(&philosophers
		->info->forks[philosophers->philo_id - 1]);
	activity(PHF, philosophers);
	pthread_mutex_lock(&philosophers->info->forks[philosophers->philo_id
		% philosophers->info->number_of_philos]);
	activity(PHF, philosophers);
	if (philosophers->info->number_of_meals != -1)
	{
		pthread_mutex_lock(&philosophers->info
			->philo_times_ate_mut[philosophers->philo_id - 1]);
		philosophers->philo_times_ate++;
		pthread_mutex_unlock(&philosophers->info
			->philo_times_ate_mut[philosophers->philo_id - 1]);
	}
	pthread_mutex_lock(&philosophers->info
		->last_meal_mut[philosophers->philo_id - 1]);
	philosophers->last_meal = current_time_ms();
	pthread_mutex_unlock(&philosophers->info
		->last_meal_mut[philosophers->philo_id - 1]);
	activity(PIE, philosophers);
}
