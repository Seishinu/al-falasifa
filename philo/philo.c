/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:44:55 by ynuiga            #+#    #+#             */
/*   Updated: 2022/05/15 11:22:51 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	philosophers_dawn(t_philo	*philosophers)
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
	while (i < philosophers->info->number_of_philos)
	{
		pthread_join(philosophers[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < philosophers->info->number_of_philos)
	{
		pthread_mutex_destroy(&philosophers->info->forks[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philosophers;
	t_info	info;
	int		i;

	error_checking(argc, argv);
	philosophers = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	info.number_of_philos = ft_atoi(argv[1]);
	info.forks = malloc(sizeof(pthread_mutex_t) * info.number_of_philos);
	info.time_to_die = ft_atoi(argv[2]);
	info.time_to_eat = ft_atoi(argv[3]);
	info.time_to_sleep = ft_atoi(argv[4]);
	info.number_of_meals = -1;
	if (argc == 6)
		info.number_of_meals = ft_atoi(argv[5]);
	info.philo_stat = 1;
	i = 0;
	while (i < info.number_of_philos)
	{
		philosophers[i].info = &info;
		if (pthread_mutex_init(&info.forks[i], NULL) != 0)
			exit (5);
		philosophers[i].philo_id = i + 1;
		if (argv[5])
			philosophers[i].philo_times_ate = 0;
		i++;
	}
	philosophers_dawn(philosophers);
	return (0);
}
