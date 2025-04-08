/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:44:03 by istripol          #+#    #+#             */
/*   Updated: 2025/04/09 00:32:12 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	res;

	sign = 0;
	res = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	while (!sign && (*nptr == '-' || *nptr == '+'))
	{
		if (*nptr == '-')
			sign = -1;
		else
			sign = 1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	if (sign < 0)
		return (res * sign);
	return (res);
}

t_bool is_number(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

void	print_timestamp(char *message, t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	// unsigned long int cur = (philo->started.tv_sec * 1000) + (philo->started.tv_usec / 1000);
	unsigned long int test = (tv.tv_sec * 1000) +  (tv.tv_usec / 1000);
	// printf("%li.%li "CYAN"Philo %i "RESET,
			// tv.tv_sec, tv.tv_usec / 1000, philo->id);

	// printf("%li "CYAN"%i "RESET, tv.tv_sec, philo->id);
	printf("%zu "CYAN"%i "RESET, test, philo->id);
	printf(message);
	// printf("\n");
}

