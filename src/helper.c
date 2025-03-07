/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:01:27 by sabdulba          #+#    #+#             */
/*   Updated: 2025/03/05 22:04:38 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	validator(int ac, char **av)
{
	if (!(ac == 6 || ac == 5))
		return (ft_error("Too few arguments.."), 1);
	while (*av++)
	{
		if (*av && is_digit(*av))
		return (ft_error("Invalid argument"), 2);
	}
	return (0);
}
