/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/25 15:45:53 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/09/06 11:48:34 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str, int i)
{
	printf("Error: %s\n", str);
	return (i);
}

void	print(t_philo *philo, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("philo %d\n", philo->position);
		philo++;
		i++;
	}
}
