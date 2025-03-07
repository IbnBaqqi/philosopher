/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:29:00 by sabdulba          #+#    #+#             */
/*   Updated: 2025/03/07 09:29:14 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_all(t_data *data, t_philo *phi)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_destroy(data->mymutex + i);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->shared);
	pthread_mutex_destroy(&data->tm);
	free(data->mymutex);
	free(data);
	free(phi);
}

void	free_single(t_data *data, t_philo *phi)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_destroy(data->mymutex + i);
	pthread_mutex_destroy(&data->print);
	free(data->mymutex);
	free(data);
	free(phi);
}
