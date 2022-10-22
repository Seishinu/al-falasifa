/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:44:55 by ynuiga            #+#    #+#             */
/*   Updated: 2022/10/21 09:45:21 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char	*str)
{
	size_t	i;
	int		sign;
	size_t	rslt;

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
	rslt = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		rslt = (rslt * 10) + (str[i] - 48);
		i++;
	}
	return (rslt * sign);
}

int	philosophers_dawn(t_philo	*philosophers)
{
	int	i;

	i = 0;
	philosophers->info->starting_time = current_time_ms();
	while (i < philosophers->info->number_of_philos)
	{
		philosophers[i].last_meal = philosophers->info->starting_time;
		pthread_create(&philosophers[i].philo, NULL,
			&routine, philosophers + i);
		usleep(50);
		i++;
	}
	philo_survival(philosophers);
	i = 0;
	if (philosophers->info->number_of_philos == 1)
		pthread_detach(philosophers->philo);
	while (i < philosophers->info->number_of_philos)
	{
		pthread_join(philosophers[i].philo, NULL);
		i++;
	}
	mutex_destroyer(philosophers);
	return (0);
}

int	mutex_initialize(t_philo	*philosophers, t_info	*info, char	**argv)
{
	int	i;

	i = 0;
	while (i < info->number_of_philos)
	{
		philosophers[i].info = info;
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (ECM);
		if (pthread_mutex_init(&info->last_meal_mut[i], NULL) != 0)
			return (ECM);
		if (pthread_mutex_init(&info->philo_times_ate_mut[i], NULL) != 0)
			return (ECM);
		philosophers[i].philo_id = i + 1;
		if (argv[5])
			philosophers[i].philo_times_ate = 0;
		i++;
	}
	if (pthread_mutex_init(info->philo_stat_mut, NULL))
		return (ECM);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philosophers;
	t_info	info;

	if (!error_checking(argc, argv))
	{
		philosophers = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
		info.number_of_philos = ft_atoi(argv[1]);
		info.forks = malloc(sizeof(pthread_mutex_t) * info.number_of_philos);
		info.last_meal_mut = malloc(sizeof(pthread_mutex_t)
				* info.number_of_philos);
		info.philo_times_ate_mut = malloc(sizeof(pthread_mutex_t)
				* info.number_of_philos);
		info.philo_stat_mut = malloc(sizeof(pthread_mutex_t));
		info.time_to_die = ft_atoi(argv[2]);
		info.time_to_eat = ft_atoi(argv[3]);
		info.time_to_sleep = ft_atoi(argv[4]);
		info.number_of_meals = -1;
		info.philo_stat = 1;
		if (argc == 6)
			info.number_of_meals = ft_atoi(argv[5]);
		mutex_initialize(philosophers, &info, argv);
		philosophers_dawn(philosophers);
	}
	return (0);
}
