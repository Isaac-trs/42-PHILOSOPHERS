/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:29:36 by istripol          #+#    #+#             */
/*   Updated: 2025/05/28 19:26:24 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	lock_forks(void *philo)
{
	if (((t_philo *)philo)->id % 2 == 0)
	{
		pthread_mutex_lock(&((t_philo *)philo)->right_fork->mutex);
		print_timestamp(ORANGE" has taken a fork\n"RESET, ((t_philo *)philo));
		pthread_mutex_lock(&((t_philo *)philo)->left_fork->mutex);
		print_timestamp(ORANGE" has taken a fork\n"RESET, ((t_philo *)philo));
	}
	else
	{
		pthread_mutex_lock(&((t_philo *)philo)->left_fork->mutex);
		print_timestamp(ORANGE" has taken a fork \n"RESET, ((t_philo *)philo));
		pthread_mutex_lock(&((t_philo *)philo)->right_fork->mutex);
		print_timestamp(ORANGE" has taken a fork \n"RESET, ((t_philo *)philo));
	}
}

static void	unlock_forks(void *philo)
{
	if (((t_philo *)philo)->id % 2 == 0)
	{
		pthread_mutex_unlock(&((t_philo *)philo)->right_fork->mutex);
		pthread_mutex_unlock(&((t_philo *)philo)->left_fork->mutex);
	}
	else
	{
		pthread_mutex_unlock(&((t_philo *)philo)->left_fork->mutex);
		pthread_mutex_unlock(&((t_philo *)philo)->right_fork->mutex);
	}
}

static void	*eating(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->program->nb_philos == 1)
	{
		print_timestamp(ORANGE" has taken a fork\n"RESET, philo);
		ft_usleep(philo->program->time_to_die);
	}
	else
	{
		pthread_mutex_lock(& philo->meal_mutex);
		philo->last_meal = get_time_ms();
		pthread_mutex_unlock(& philo->meal_mutex);
		lock_forks(philo);
		print_timestamp(YELLOW" is eating\n"RESET, philo);
		ft_usleep(philo->time_to_eat);
		unlock_forks(philo);
		print_timestamp(GREEN" finished eating\n"RESET, philo);
		print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
		pthread_mutex_lock(& philo->meal_mutex);
		philo->nb_meals++;
		pthread_mutex_unlock(& philo->meal_mutex);
	}
	return (NULL);
}

static void	*sleeping(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	print_timestamp(YELLOW" is sleeping\n"RESET, philo);
	ft_usleep(philo->time_to_sleep);
	print_timestamp(GREEN" finished sleeping\n"RESET, philo);
	print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
	return (NULL);
}

void	*start_routine(void *philo)
{
	if (((t_philo *)philo)->id % 2 != 0)
		ft_usleep(1);
	pthread_mutex_lock(&((t_philo *)philo)->meal_mutex);
	((t_philo *)philo)->last_meal = get_time_ms();
	pthread_mutex_unlock(&((t_philo *)philo)->meal_mutex);
	while (1)
	{
		if (((t_philo *)philo)->id % 2 != 0)
		{
			if (check_death_lock(((t_philo *)philo)->program) == 1)
				break ;
			sleeping((t_philo *)philo);
			if (check_death_lock(((t_philo *)philo)->program) == 1)
				break ;
			eating((t_philo *)philo);
		}
		else
		{
			eating((t_philo *)philo);
			if (check_death_lock(((t_philo *)philo)->program) == 1)
				break ;
			sleeping((t_philo *)philo);
			if (check_death_lock(((t_philo *)philo)->program) == 1)
				break ;
		}
	}
	return ((int *)1);
}
