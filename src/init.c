/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:11:14 by sabdulba          #+#    #+#             */
/*   Updated: 2025/04/04 08:13:13 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_fork_lock(t_info *info);
static int	min_i(int first, int second);
static int	max_i(int first, int second);

void	ph_init_mutexes(t_info *info)
{
	init_fork_lock(info);
	if (0 != pthread_mutex_init(&info->print_lock, NULL))
	{
		ph_mutexes_destroy(info->fork_lock, info->forks);
		free(info->fork_lock);
		ph_exit(ERROR_MUTEX_INIT);
	}
	if (0 != pthread_mutex_init(&info->time_lock, NULL))
	{
		ph_mutexes_destroy(info->fork_lock, info->forks);
		ph_mutexes_destroy(&info->print_lock, 1);
		free(info->fork_lock);
		ph_exit(ERROR_MUTEX_INIT);
	}
}

static void	init_fork_lock(t_info *info)
{
	int	i;

	info->fork_lock = malloc(info->forks * sizeof(pthread_mutex_t));
	if (!info->fork_lock)
		ph_exit(ERROR_MALLOC);
	info->fork_bool = malloc(info->forks * sizeof(bool));
	if (!info->fork_bool)
	{
		free(info->fork_lock);
		ph_exit(ERROR_MALLOC);
	}
	i = 0;
	while (i < info->forks)
	{
		info->fork_bool[i] = false;
		if (0 != pthread_mutex_init(&info->fork_lock[i], NULL))
		{
			ph_mutexes_destroy(info->fork_lock, i);
			free(info->fork_lock);
			free(info->fork_bool);
			ph_exit(ERROR_MUTEX_INIT);
		}
		i++;
	}
}

void	ph_init_philosophers(t_info *info, t_philo **philo)
{
	t_philo	*ph;
	int		i;

	ph = malloc(info->forks * sizeof(t_philo));
	if (!ph)
		ph_destroy_and_exit(ERROR_MALLOC, info, ph);
	i = 0;
	while (i < info->forks)
	{
		ph[i].info = info;
		ph[i].num = i + 1;
		ph[i].first_lock = &info->fork_lock[min_i(i, (i + 1) % info->forks)];
		ph[i].second_lock = &info->fork_lock[max_i(i, (i + 1) % info->forks)];
		ph[i].first_bool = &info->fork_bool[min_i(i, (i + 1) % info->forks)];
		ph[i].second_bool = &info->fork_bool[max_i(i, (i + 1) % info->forks)];
		ph[i].last_meal_ms = 0;
		ph[i].meals_done = 0;
		ph[i].delay_first_meal = (0 != ph[i].num % 2);
		i++;
	}
	*philo = ph;
}

static int	min_i(int first, int second)
{
	if (first < second)
		return (first);
	return (second);
}

static int	max_i(int first, int second)
{
	if (first > second)
		return (first);
	return (second);
}
