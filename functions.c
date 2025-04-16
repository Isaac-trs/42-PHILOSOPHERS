/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:44:03 by istripol          #+#    #+#             */
/*   Updated: 2025/04/15 09:02:44 by istripol         ###   ########.fr       */
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

t_bool	is_number(char *str)
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
	// struct timeval	tv;

	long long now;
	pthread_mutex_lock(philo->write_lock);
	now = get_time_ms();
	// unsigned long int cur = (philo->started.tv_usec / 1000) + (philo->started.tv_sec * 1000);
	// unsigned long int test = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) ;
	// printf("%zu "CYAN"Philo %i "RESET, test - cur, philo->id);

	printf(BOLD"%lli"RESET CYAN" %i"RESET, now, philo->id);
	printf(message);
	pthread_mutex_unlock(philo->write_lock);

	// printf("\n");
}

long long get_time_ms()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

void	clean_exit(t_program *program, t_flag flag, int thread)
{
	int	j;

	pthread_mutex_lock(& program->write_lock);
	j = 0;
	// int i = 0;
	if (flag == philosophers)
		exit(1);
	if (flag != forking)	
		while (j < program->nb_philos )
		{
			pthread_mutex_lock(& program->forks[j].mutex);
			pthread_mutex_unlock(& program->forks[j].mutex);
			pthread_mutex_destroy(& program->forks[j].mutex);
			pthread_mutex_destroy(& program->philos[j++].meal_mutex);
		}
	if (flag == threadd)
		while (j <= thread)
			pthread_detach(program->philos[j++].thread);
	if (flag == null || flag == threadd || flag == forking)
	{
		if (flag != forking)
			free(program->forks);
		free(program->philos);
		exit(1);
	}
	pthread_mutex_unlock(& program->write_lock);
	pthread_mutex_destroy(& program->write_lock);
	pthread_mutex_destroy(& program->dead_lock);
	free(program->forks);
	free(program->philos);
	exit(0);
}

