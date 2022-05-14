/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:33:40 by ynuiga            #+#    #+#             */
/*   Updated: 2022/05/14 18:08:29 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# define AMD -1
# define WNA -2
# define CVA -3
# define PHF 1
# define PIE 2
# define PIS 3
# define PIT 4

typedef struct s_info
{
	pthread_mutex_t	*forks;
	long			number_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			starting_time;
	int				philo_stat;
	long			number_of_meals;
}					t_info;

typedef struct s_philo
{
	t_info			*info;
	pthread_t		philo;
	int				philo_id;
	long			last_meal;
	long			philo_times_ate;
}					t_philo;

long	current_time_ms(void);
void	*routine(void	*param);
void	philo_survival(t_philo	*philosophers);
void	error_checking(int argc, char	**argv);
int		ft_atoi(const char	*str);
int		ft_isdigit(int c);

#endif