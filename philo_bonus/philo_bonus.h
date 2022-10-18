/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:58:38 by ynuiga            #+#    #+#             */
/*   Updated: 2022/05/16 20:36:09 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
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
	int				number_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			starting_time;
	long			number_of_meals;
	long			philo_times_ate;
}					t_info;

typedef struct s_philo
{
	t_info			*info;
	sem_t			*semaprint;
	pthread_t		philo;
	int				philo_id;
	long			last_meal;
	pid_t			*philo_pid;
}					t_philo;

void	error_checking_b(int argc, char **argv);
int		ft_atoi(const char	*str);
int		ft_isdigit(int c);
long	current_time_ms(void);

#endif