/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:15:37 by sabdulba          #+#    #+#             */
/*   Updated: 2025/03/07 09:25:16 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	handle_actions(t_philo *phi)
{
	if (!philo_eat(phi))
		return (0);
	if (phi->n_eaten != phi->data->n_eat)
	{
		if (!philo_sleep(phi))
			return (0);
		if (!philo_think(phi))
			return (0);
	}
	return (1);
}

void	*monitor(void *args)
{
	t_philo	*phi;
	int		i;

	i = 0;
	phi = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&phi->data->shared);
		if (((phi->data->n_eat > 0 && phi[i].data->n_eat > phi[i].n_eaten)
				|| phi->data->n_eat < 0)
			&& !phi[i].data->philo_died)
		{
			pthread_mutex_unlock(&phi->data->shared);
			if (is_dead(phi, &i))
				break ;
		}
		else
		{
			pthread_mutex_unlock(&phi->data->shared);
			break ;
		}
	}
	return (NULL);
}

void	*handle_philo(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&phi->data->shared);
		if (((phi->data->n_eat > 0 && phi->data->n_eat > phi->n_eaten)
				|| phi->data->n_eat < 0)
			&& !phi->data->philo_died)
		{
			pthread_mutex_unlock(&phi->data->shared);
			if (!handle_actions(phi))
				break ;
		}
		else
		{
			pthread_mutex_unlock(&phi->data->shared);
			break ;
		}
	}
	return (NULL);
}
