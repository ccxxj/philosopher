/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/02 21:57:50 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/09/14 20:10:30 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_time(void *arg)
{
	t_philo			*philo;
	struct timeval	now;
	long			time_elapse;

	philo = (t_philo *)arg;
	while (!philo->data->death)
	{
		if (philo->data->status_data == inactive)
			break ;
		pthread_mutex_lock(&(philo->mutex));
		gettimeofday(&now, NULL);
		time_elapse = calculate_time(&(philo->last_eaten), &now);
		pthread_mutex_unlock(&(philo->mutex));
		if (time_elapse >= philo->data->input.time_die)
		{
			philo->data->death = 1;
			pthread_mutex_lock(&(philo->data->print_mutex));
			printf("%ld %d %s\n", calculate_time(&(philo->start), &now),
				philo->position, "died");
			pthread_mutex_unlock(&(philo->data->print_mutex));
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
