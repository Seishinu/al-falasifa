/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:46:37 by ynuiga            #+#    #+#             */
/*   Updated: 2022/10/22 16:05:37 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char	*str)
{
	size_t	rslt;
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
	rslt = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		rslt = (rslt * 10) + (str[i] - 48);
		i++;
	}
	return (rslt * sign);
}

void	prep_to_eat(t_philo	*philosophers)
{
	sem_wait(philosophers->forks);
	food_activity(PHF, philosophers);
	sem_wait(philosophers->forks);
	food_activity(PHF, philosophers);
}
