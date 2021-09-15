/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/31 22:12:40 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/09/15 14:13:18 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(struct timeval *start, long n, t_philo *philo)
{
	struct timeval	end;
	int				a;

	gettimeofday(&end, NULL);
	a = 0;
	while (calculate_time(start, &end) < n && !philo->data->death
		&& philo->data->status_data == active)
	{
		usleep(100);
		gettimeofday(&end, NULL);
		a++;
	}
}

void	try_sleep(t_philo *philo)
{
	struct timeval	now;

	print_msg(&(philo->start), philo->position, "is sleeping", philo);
	gettimeofday(&now, NULL);
	ft_sleep(&(now), philo->data->input.time_sleep, philo);
	print_msg(&(philo->start), philo->position, "is thinking", philo);
}

void	*single_rountine(t_philo *philo)
{
	print_msg(&(philo->start), philo->position, "has taken a fork", philo);
	ft_sleep(&(philo->start), philo->data->input.time_die, philo);
	print_msg(&(philo->start), philo->position, "died", philo);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	gettimeofday(&(philo->start), NULL);
	if (philo->data->input.number == 1)
		return (single_rountine(philo));
	philo->last_eaten = philo->start;
	if (pthread_create(&(philo->monitor), NULL, check_time, philo) != 0)
	{
		ft_error("thread cannot be created", 1);
		philo->data->death = 1;
		return (NULL);
	}
	while (1)
	{
		if (philo->data->death || philo->data->status_data == inactive)
			break ;
		try_eat(philo);
		try_sleep(philo);
	}
	pthread_join(philo->monitor, NULL);
	return (NULL);
}
