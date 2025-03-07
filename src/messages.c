/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:32:54 by sabdulba          #+#    #+#             */
/*   Updated: 2025/03/07 09:33:09 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_state(t_philo *phi, int id, char *color, char *status)
{
	long long	now;

	now = time_diff(phi->data->timer);
	pthread_mutex_lock(&phi->data->print);
	pthread_mutex_lock(&phi->data->shared);
	if (phi->data->philo_died)
	{
		pthread_mutex_unlock(&phi->data->shared);
		pthread_mutex_unlock(&phi->data->print);
		return (0);
	}
	else
		printf("%s%-10lld %-3d %-30s%s\n", color, now, id, status, NONE);
	pthread_mutex_unlock(&phi->data->shared);
	pthread_mutex_unlock(&phi->data->print);
	return (1);
}
