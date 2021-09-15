/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:03:43 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/09/14 13:40:29 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n == 0 || n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	get_digits(char *str, unsigned int n)
{
	if (n == 0)
		*str = '0';
	while (n != 0)
	{
		*str = n % 10 + '0';
		str--;
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_numlen(n) + 1;
	str = malloc(len * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len - 1] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	get_digits(str + len - 2, n);
	return (str);
}
