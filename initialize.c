/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/28 20:46:28 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/09/15 14:22:03 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arg(char *str, long *nbr)
{
	long	n;
	char	*str2;

	n = ft_atoi(str);
	str2 = ft_itoa(n);
	if (!str2)
		return (ft_error("malloc fail", 1));
	if (ft_strcmp(str, str2) != 0)
	{
		free(str2);
		return (ft_error("invalid input", 1));
	}
	free(str2);
	*nbr = n;
	return (0);
}

int	initialize_fork(pthread_mutex_t **fork, int n, t_data *data)
{
	int	i;

	i = 0;
	*fork = malloc(n * sizeof(pthread_mutex_t));
	if (!fork)
		return (ft_error("malloc fail", 1));
	while (i < n)
	{
		if (pthread_mutex_init(&(*fork)[i], NULL) != 0)
		{
			mutex_destroy(*fork, i);
			return (ft_error("mutex initialization fail", 1));
		}
		i++;
	}
	return (0);
}

int	update_input(t_data *data, char **argv)
{
	if (parse_arg(argv[1], &(data->input.number)))
		return (1);
	if (parse_arg(argv[2], &(data->input.time_die)))
		return (1);
	if (parse_arg(argv[3], &(data->input.time_eat)))
		return (1);
	if (parse_arg(argv[4], &(data->input.time_sleep)))
		return (1);
	return (0);
}

int	initialize_data(char **argv, t_data *data)
{
	data->death = 0;
	data->status_data = active;
	data->input.optional = -1;
	if (argv[5])
	{
		data->input.optional = ft_atoi(argv[5]);
		data->eat_times = 0;
	}
	pthread_mutex_init(&(data->print_mutex), NULL);
	return (0);
}

t_philo	*initialize_philo(t_philo *philo, t_data *data,
	pthread_mutex_t *fork, pthread_mutex_t *freeze)
{
	int	i;
	int	number;

	i = 0;
	number = data->input.number;
	philo = malloc(number * sizeof(t_philo));
	if (!philo)
	{
		ft_error("malloc fail", 1);
		return (NULL);
	}
	while (i < number)
	{
		philo[i].left_fork = &fork[i];
		philo[i].right_fork = &fork[(i + 1) % number];
		philo[i].current_freeze = &freeze[i];
		philo[i].next_freeze = &freeze[(i + 1) % number];
		philo[i].position = i + 1;
		philo[i].data = data;
		philo[i].times_eat = 0;
		pthread_mutex_init(&(philo[i].mutex), NULL);
		i++;
	}
	return (philo);
}
