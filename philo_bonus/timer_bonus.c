/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynuiga <ynuiga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 10:29:22 by ynuiga            #+#    #+#             */
/*   Updated: 2022/05/15 11:35:43 by ynuiga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo_bonus.h"

long	current_time_ms()
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}