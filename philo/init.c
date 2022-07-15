/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaby <afaby@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:06:22 by afaby             #+#    #+#             */
/*   Updated: 2022/07/15 14:26:58 by afaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, char *argv[])
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (data->nb_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (0);
	return (1);
}
