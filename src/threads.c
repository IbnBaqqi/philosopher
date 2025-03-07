/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:09:34 by sabdulba          #+#    #+#             */
/*   Updated: 2025/03/07 09:12:11 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	handle_thread(t_philo *phi)
{
	int	i;

	i = 0;
	if (pthread_create(&phi[i].data->monitor, NULL, monitor, phi))
		return (ft_error("Failed to create thread"), 1);
	phi->data->timer = get_time();
	while (i < phi->data->philo_num)
	{
		if (pthread_create(&phi[i].th, NULL, handle_philo, &phi[i]))
			return (ft_error("Failed to create thread"), 0);
		i++;
		usleep(1000);
	}
	i = 0;
	while (i < phi->data->philo_num)
		if (pthread_join(phi[i++].th, NULL))
			return (ft_error("Failed to join thread"), 0);
	if (pthread_join(phi->data->monitor, NULL))
		return (ft_error("Failed to join thread"), 0);
	return (1);
}
