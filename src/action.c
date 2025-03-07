/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:26:56 by sabdulba          #+#    #+#             */
/*   Updated: 2025/03/07 09:27:22 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_eat(t_philo *phi)
{
	pthread_mutex_lock(&phi->data->mymutex[phi->hand.left]);
	if (!print_state(phi, phi->phi_id + 1, NONE, L_FORK))
		return (drop_forks(phi, 1), 0);
	pthread_mutex_lock(&phi->data->mymutex[phi->hand.right]);
	if (!print_state(phi, phi->phi_id + 1, NONE, R_FORK))
		return (drop_forks(phi, 2), 0);
	if (!print_state(phi, phi->phi_id + 1, GREEN, EAT))
		return (drop_forks(phi, 2), 0);
	pthread_mutex_lock(&phi->data->tm);
	phi->t_die = get_time();
	pthread_mutex_unlock(&phi->data->tm);
	time_sim(phi->data->time.to_eat);
	drop_forks(phi, 2);
	pthread_mutex_lock(&phi->data->shared);
	phi->n_eaten++;
	pthread_mutex_unlock(&phi->data->shared);
	return (1);
}

int	philo_sleep(t_philo *phi)
{
	if (!print_state(phi, phi->phi_id + 1, NONE, SLEEP))
		return (0);
	time_sim(phi->data->time.to_sleep);
	return (1);
}

int	philo_think(t_philo *phi)
{
	if (!print_state(phi, phi->phi_id + 1, NONE, THINK))
		return (0);
	return (1);
}

int	is_dead(t_philo *phi, int *i)
{
	long long	time;

	if (*i == phi[*i].data->philo_num)
	{
		*i = 0;
		usleep(200);
	}
	pthread_mutex_lock(&phi->data->tm);
	time = time_diff(phi[*i].t_die);
	if (time > phi[*i].data->time.to_die)
	{
		pthread_mutex_unlock(&phi->data->tm);
		print_state(&phi[*i], phi[*i].phi_id + 1, RED, DIED);
		pthread_mutex_lock(&phi->data->shared);
		phi[*i].data->philo_died = 1;
		pthread_mutex_unlock(&phi->data->shared);
		return (1);
	}
	pthread_mutex_unlock(&phi->data->tm);
	*i += 1;
	return (0);
}

void	drop_forks(t_philo *phi, int flag)
{
	pthread_mutex_unlock(&phi->data->mymutex[phi->hand.left]);
	if (flag == 2)
		pthread_mutex_unlock(&phi->data->mymutex[phi->hand.right]);
}
