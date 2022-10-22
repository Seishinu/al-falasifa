/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spxactivities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:50:16 by ynuiga            #+#    #+#             */
/*   Updated: 2022/10/22 15:59:44 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philo_survival(void	*param)
{
	t_philo	*philosophers;
	long	difference;

	philosophers = (t_philo *)param;
	while (1)
	{
		difference = current_time_ms() - philosophers->last_meal;
		if (philosophers->time_to_die <= difference)
		{
			sem_wait(philosophers->semaprint);
			printf("%ldms\t%d is DEAD!\n",
				current_time_ms() - philosophers->starting_time,
				philosophers->philo_id);
			exit(0);
		}
		else if (philosophers->number_of_meals != -1 && \
				philosophers->philo_times_ate >= philosophers->number_of_meals)
			exit (1);
	}
	return (0);
}

void	food_activity(int action, t_philo	*philosophers)
{
	if (action == PHF)
	{
		sem_wait(philosophers->semaprint);
		printf("%ldms\t%d has taken a fork\n",
			current_time_ms() - philosophers->starting_time,
			philosophers->philo_id);
		sem_post(philosophers->semaprint);
	}
	else if (action == PIE)
	{
		sem_wait(philosophers->semaprint);
		printf("%ldms\t%d is eating\n",
			current_time_ms() - philosophers->starting_time,
			philosophers->philo_id);
		sem_post(philosophers->semaprint);
	}
}

void	other_activities(int action, t_philo	*philosophers)
{
	if (action == PIS)
	{
		sem_wait(philosophers->semaprint);
		printf("%ldms\t%d is sleeping\n",
			current_time_ms() - philosophers->starting_time,
			philosophers->philo_id);
		sem_post(philosophers->semaprint);
	}
	else if (action == PIT)
	{
		sem_wait(philosophers->semaprint);
		printf("%ldms\t%d is thinking\n",
			current_time_ms() - philosophers->starting_time,
			philosophers->philo_id);
		sem_post(philosophers->semaprint);
	}
}
