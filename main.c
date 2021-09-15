/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 08:50:00 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/09/15 14:53:44 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo *philo, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&(philo[i].pid), NULL, routine, &philo[i]) == 0)
			i++;
		else
			return (ft_error("thread cannot be created", 1));
	}
	return (0);
}

void	join_threads(t_philo *philo)
{
	int	i;

	i = philo->data->input.number - 1;
	while (i >= 0)
	{
		if (pthread_join(philo[i].pid, NULL) != 0)
			printf("pthread_join error\n");
		i--;
	}
}

int	free_routine(t_data *data, t_philo *philo, pthread_mutex_t	*forks,
	pthread_mutex_t	*freeze)
{
	int	n;

	n = philo->data->input.number;
	if (forks)
	{
		mutex_destroy(forks, n);
		free(forks);
	}
	if (freeze)
	{
		mutex_destroy(freeze, n);
		free(freeze);
	}
	n = philo->data->input.number - 1;
	if (philo && n >= 0)
	{
		pthread_mutex_destroy(&(philo[n].mutex));
		n--;
	}
	if (philo)
		free(philo);
	pthread_mutex_destroy(&data->print_mutex);
	return (1);
}

int	check_input(char argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_error("argument number is incorrect!", 1));
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0
		|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (ft_error("argument need to be positive number!", 1));
	if (argv[5])
	{
		if (ft_atoi(argv[1]) <= 0)
			return (ft_error("argument need to be positive number!", 1));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*freeze;
	t_data			data;

	if (check_input(argc, argv))
		return (1);
	philo = NULL;
	if (update_input(&data, argv))
		return (1);
	if (initialize_data(argv, &data))
		return (1);
	if (initialize_fork(&forks, data.input.number, &data))
		return (1);
	if (initialize_fork(&freeze, data.input.number, &data))
		return (free_routine(&data, philo, forks, freeze));
	philo = initialize_philo(philo, &data, forks, freeze);
	if (!philo)
		return (free_routine(&data, philo, forks, freeze));
	if (create_threads(philo, data.input.number) == 1)
		return (free_routine(&data, philo, forks, freeze));
	join_threads(philo);
	free_routine(&data, philo, forks, freeze);
	return (0);
}
