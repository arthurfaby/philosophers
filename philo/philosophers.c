/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaby <afaby@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 09:24:41 by afaby             #+#    #+#             */
/*   Updated: 2022/09/12 16:13:20 by afaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_data		data;
	pthread_t	checker;

	if (argc < 5 || argc > 6)
	{
		write(2, "Usage: ./philo nb_philos ttd tte tts [nb_eat]\n", 46);
		return (1);
	}	
	if (!init_data(&data, argv, argc))
	{
		write(2, "Error: range: ./philo [1 - 2147483647] "
			"[1 - 2147483647] [1 - 2147483647] [1 - 2147483647] "
			"[1 - 2147483647].\n", 108);
		return (2);
	}
	launch_philos(&data, &checker);
	free_data(&data);
	return (0);
}
