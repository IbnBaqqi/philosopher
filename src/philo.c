/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:29:14 by sabdulba          #+#    #+#             */
/*   Updated: 2025/03/07 09:12:39 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	single_philo(t_data *data, t_philo *phi)
{
	data->timer = get_time();
	print_state(phi, 1, NONE, L_FORK);
	time_sim(data->time.to_die);
	print_state(phi, 1, RED, DIED);
	free_all(data, phi);
	return (0);
}

int main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (validator(ac, av))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error("Memory allocation failed"), 2);
	if (!init_data(data, av, ac))
		return (2);
	if (!mutex_init(data))
		return (3);
	philo = malloc(sizeof(t_philo) * (data->philo_num + 1));
	if (!philo)
		return (ft_error("Memory allocation failed"), 4);
	init_philo(philo, data);
	if (data->philo_num == 1)
		return (single_philo(data, philo));
	if (!handle_thread(philo)) // Todo
		return (free_all(data, philo), 6); //Todo
}
