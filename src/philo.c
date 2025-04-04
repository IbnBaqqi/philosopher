/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:29:14 by sabdulba          #+#    #+#             */
/*   Updated: 2025/04/04 08:08:46 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philo;

	philo = NULL;
	memset(&info, 0, sizeof(t_info));
	ph_parse_argv(argc, argv, &info);
	ph_init_mutexes(&info);
	ph_init_philosophers(&info, &philo);
	ph_create_threads(&info, philo);
	ph_pthread_join(&info, philo);
	ph_destroy_and_exit(EXIT_SUCCESS, &info, philo);
}
