/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:33:40 by ynuiga            #+#    #+#             */
/*   Updated: 2022/10/18 10:52:16 by ynuiga           ###   ########.fr       */
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

# define SUC 0
# define AMD 1
# define WNA 2
# define CVA 3
# define ECM 4
# define EJT 5
# define PID 6
# define PAE 7
# define PHF 8
# define PIE 9
# define PIS 10
# define PIT 11

typedef struct s_info
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*last_meal_mut;
	pthread_mutex_t	*philo_times_ate_mut;
	pthread_mutex_t	*philo_stat_mut;
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

void	mutex_destroyer(t_philo	*philosophers);
void	dead_end(t_philo *philosophers, long difference, int i);
long	current_time_ms(void);
void	*routine(void	*param);
void	philo_survival(t_philo	*philosophers);
int		error_checking(int argc, char	**argv);
int		ft_atoi(const char	*str);
int		ft_isdigit(int c);
void	food_time(t_philo *philosophers);
void	activity(int action, t_philo *philosophers);

#endif