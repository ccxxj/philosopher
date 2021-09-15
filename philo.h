/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/24 11:58:39 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/09/15 14:29:45 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo.h"
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_input
{
	long	number;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		optional;
	int		position;
}	t_input;

enum	e_status
{
	active,
	inactive
};

/* this struct is to store the shared data */
typedef struct s_data
{
	t_input			input;
	int				death;
	int				eat_times;
	int				status_data;
	pthread_mutex_t	print_mutex;
}	t_data;

/* this struct is to store the information per philosopher */
typedef struct s_philo
{
	pthread_t		pid;
	pthread_t		monitor;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*current_freeze;
	pthread_mutex_t	*next_freeze;
	struct timeval	start;
	struct timeval	last_eaten;
	int				position;
	int				times_eat;
	t_data			*data;
}	t_philo;

int		ft_atoi(const char *str);
int		ft_error(char *str, int i);
void	*routine(void *arg);
int		initialize_fork(pthread_mutex_t **fork, int n, t_data *data);
int		initialize_data(char **argv, t_data *data);
int		update_input(t_data *data, char **argv);
t_philo	*initialize_philo(t_philo *philo, t_data *data,
			pthread_mutex_t *fork, pthread_mutex_t *freeze);
void	ft_sleep(struct timeval *start, long n, t_philo *philo);
long	calculate_time(struct timeval *start, struct timeval *end);
void	*check_time(void *arg);
void	try_eat(t_philo *philo);
void	print_msg(struct timeval *start, int n, char *str, t_philo *philo);
void	mutex_destroy(pthread_mutex_t *fork, int n);
char	*ft_itoa(int n);
int		ft_strcmp(char *a, char *b);

#endif
