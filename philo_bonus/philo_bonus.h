/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:58:38 by ynuiga            #+#    #+#             */
/*   Updated: 2022/10/22 16:05:08 by ynuiga           ###   ########.fr       */
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
# define PAE 5

typedef struct s_philo
{
	sem_t			*semaprint;
	sem_t			*forks;
	pthread_t		philo;
	long			last_meal;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			starting_time;
	long			number_of_meals;
	long			philo_times_ate;
	pid_t			*philo_pid;
	int				philo_id;
	int				number_of_philos;
}					t_philo;

void	error_checking_b(int argc, char **argv);
int		ft_atoi(const char	*str);
int		ft_isdigit(int c);
void	prep_to_eat(t_philo	*philosophers);
long	current_time_ms(void);
void	food_activity(int action, t_philo	*philosophers);
void	other_activities(int action, t_philo	*philosophers);
void	*philo_survival(void	*param);

#endif