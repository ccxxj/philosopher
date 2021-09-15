/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/05 19:49:00 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/09/15 14:26:54 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(struct timeval *start, int n, char *str, t_philo *philo)
{
	struct timeval	now;
	long			time_elapse;

	gettimeofday(&now, NULL);
	time_elapse = calculate_time(start, &now);
	if (!philo->data->death && philo->data->status_data == active)
	{
		pthread_mutex_lock(&(philo->data->print_mutex));
		printf("%ld %d %s\n", time_elapse, n, str);
		pthread_mutex_unlock(&(philo->data->print_mutex));
	}
}

long	calculate_time(struct timeval *start, struct timeval *end)
{
	long	time_taken;

	time_taken = end->tv_sec - start->tv_sec;
	time_taken = time_taken * 1e3 + (end->tv_usec - start->tv_usec) * 1e-3;
	return (time_taken);
}

void	mutex_destroy(pthread_mutex_t *fork, int n)
{
	while (n > 0)
	{
		pthread_mutex_destroy(&(fork[n - 1]));
		n--;
	}
}

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] != '\0' || b[i] != '\0')
	{
		if (a[i] != b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	return (0);
}
