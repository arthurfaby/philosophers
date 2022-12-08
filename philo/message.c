/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaby <afaby@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:38:59 by afaby             #+#    #+#             */
/*   Updated: 2022/09/08 17:05:00 by afaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_data *data, int philo, char *msg)
{
	struct timeval	now;
	long			m_now;
	long			timestamp;

	pthread_mutex_lock(&data->m_message);
	gettimeofday(&now, NULL);
	m_now = now.tv_sec * 1000 + now.tv_usec / 1000;
	timestamp = m_now - data->start;
	pthread_mutex_lock(&data->m_finished);
	if (!data->finished)
		printf("%ld %d %s", timestamp, philo, msg);
	pthread_mutex_unlock(&data->m_finished);
	pthread_mutex_unlock(&data->m_message);
}
