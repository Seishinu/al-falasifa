/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:20:23 by ynuiga            #+#    #+#             */
/*   Updated: 2022/05/15 10:14:24 by ynuiga           ###   ########.fr       */
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

void	routine(sem_t	*semaphilo, t_philo	*philosophers)
{
	sem_wait(semaphilo);
	sleep(1);
	printf("hello from the process child my philo id is %d out of %ld\n", philosophers->philo_id, philosophers->info->number_of_philos);
	sem_post(semaphilo);
	exit (0);
}


int	main(int	argc, char	**argv)
{
	t_philo	*philosophers;
	t_info	info;
	sem_t	*semaphilo;
	int		i;
	pid_t	id;

	i = 0;
	error_checking_b(argc, argv);
	philosophers = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	info.number_of_philos = ft_atoi(argv[1]);
	info.time_to_die = ft_atoi(argv[2]);
	info.time_to_eat = ft_atoi(argv[3]);
	info.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info.number_of_meals = ft_atoi(argv[5]);
	sem_unlink("semaphilos");
	semaphilo = sem_open("semaphilos", O_CREAT, 0644, 1);
	while (i < info.number_of_philos)
	{
		id = fork ();
		if (id == -1)
			exit (1);
		else if(id == 0)
		{
			philosophers->info = &info;
			philosophers->philo_id = i + 1;
			routine(semaphilo, philosophers);
		}
		i++;
	}
	while (wait(NULL) != -1)
		;
	return (0);
}
