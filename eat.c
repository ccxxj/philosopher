/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/31 22:59:31 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/09/15 14:10:40 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(pthread_mutex_t *fork1,
	pthread_mutex_t *fork2, t_philo *philo)
{
	pthread_mutex_lock(philo->current_freeze);
	pthread_mutex_lock(fork1);
	pthread_mutex_unlock(philo->current_freeze);
	pthread_mutex_lock(philo->next_freeze);
	print_msg(&(philo->start), philo->position, "has taken a fork", philo);
	pthread_mutex_lock(fork2);
	print_msg(&(philo->start), philo->position, "has taken a fork", philo);
	print_msg(&(philo->start), philo->position, "is eating", philo);
}

static void	pick_up_forks(pthread_mutex_t *fork1,
	pthread_mutex_t *fork2, t_philo *philo)
{
	struct timeval	now;

	lock_forks(fork1, fork2, philo);
	pthread_mutex_lock(&(philo->mutex));
	gettimeofday(&(philo->last_eaten), NULL);
	pthread_mutex_unlock(&(philo->mutex));
	if (philo->data->input.optional > 0 && !philo->data->death
		&& philo->data->status_data == active)
	{
		philo->times_eat++;
		if (philo->data->input.optional > 0
			&& philo->times_eat == philo->data->input.optional)
		{
			philo->data->eat_times++;
			if (philo->data->eat_times == philo->data->input.number)
				philo->data->status_data = inactive;
		}
	}
	gettimeofday(&now, NULL);
	ft_sleep(&(now), philo->data->input.time_eat, philo);
	pthread_mutex_unlock(fork2);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(philo->next_freeze);
}

void	try_eat(t_philo *philo)
{
	struct timeval	now;

	if (!philo->data->death && philo->data->status_data == active)
	{
		if ((philo->position % 2))
			pick_up_forks(philo->left_fork, philo->right_fork, philo);
		else
		{
			usleep(100);
			pick_up_forks(philo->left_fork, philo->right_fork, philo);
		}
	}
}
