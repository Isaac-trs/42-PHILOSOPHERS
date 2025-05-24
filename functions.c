/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:44:03 by istripol          #+#    #+#             */
/*   Updated: 2025/05/24 12:09:55 by istripol         ###   ########.fr       */
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

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)(tv.tv_sec) *1000) + (tv.tv_usec) / 1000);
}

void	ft_usleep(long ms)
{
	long	now;

	now = get_time_ms();
	while (get_time_ms() - now < ms)
		usleep(10);
}

void	ft_exit(t_program *program, int flag)
{
	int	j;

	pthread_mutex_lock(& program->write_lock);
	if (flag == ERRARGS || flag == ERRPHILO)
		exit(0);
	if (flag == ERREXIT)
	{
		printf(RED"STANDARD EXIT !\n"RESET);
		j = -1;
		while (++j < program->nb_philos)
			pthread_mutex_destroy(& program->forks[j].mutex);
		free(program->forks);
	}
	if (flag == ERRFORKS || flag == ERREXIT)
	{
		printf(RED"MALLOC FORKS ERROR OR EXIT !\n"RESET);
		j = -1;
		while (++j < program->nb_philos)
			pthread_mutex_destroy(&program->philos[j].meal_mutex);
		free(program->philos);
	}
	pthread_mutex_destroy(& program->dead_lock);
	pthread_mutex_unlock(& program->write_lock);
	pthread_mutex_destroy(& program->write_lock);
	exit(0);
}
