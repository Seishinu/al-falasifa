/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:56:07 by ynuiga            #+#    #+#             */
/*   Updated: 2022/10/17 16:22:44 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_digits(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	error_checking(int argc, char	**argv)
{
	if (!all_digits(argc, argv))
	{
		write(2, "Argumentes Must be all Digits!\n", 30);
		return (AMD);
	}
	if (!(argc == 5 || argc == 6))
	{
		write(2, "Wrong Number of Arguments!\n", 27);
		return (WNA);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0 || (argc == 6 && ft_atoi(argv[5]) <= 0))
	{
		write(2, "Check the Validity of your Arguments!\n", 38);
		return (CVA);
	}
	return (SUC);
}
