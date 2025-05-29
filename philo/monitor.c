/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 01:12:00 by istripol          #+#    #+#             */
/*   Updated: 2025/05/29 06:00:16 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	check_death_lock(t_program *program)
{
	t_bool	died;

	pthread_mutex_lock(&program->dead_lock);
	died = program->foo_died;
	pthread_mutex_unlock(&program->dead_lock);
	return (died);
}

t_bool	set_death_lock(t_program *program)
{
	pthread_mutex_lock(& program->dead_lock);
	program->foo_died = 1;
	pthread_mutex_unlock(& program->dead_lock);
	return (0);
}

static t_bool	check_philo_died(t_philo	*philo)
{
	long	elapsed_meal;


	pthread_mutex_lock(& philo->meal_mutex);
	elapsed_meal = get_time_ms() - philo->last_meal;
	pthread_mutex_unlock(& philo->meal_mutex);
	if (elapsed_meal >= philo->time_to_die) // opposite for checks
	{
		// pthread_mutex_lock(philo->dead_lock);
		// philo->program->foo_died = 1;
		// pthread_mutex_unlock(philo->dead_lock);
		set_death_lock(philo->program);
		pthread_mutex_lock(philo->write_lock);
		// printf(BOLD"%lli "RESET, get_time_ms());
		printf(BOLD"%lli "RESET CYAN"%i" RED" DIED\n"RESET, get_time_ms(), philo->id);
		printf("elapsed meal from philo %i %li\n", philo->id, elapsed_meal);
		pthread_mutex_unlock(philo->write_lock);
		return (1);
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_program		*program;
	int				i;
	unsigned int	total_meals;
	unsigned int	target_meals;

	program = (t_program *)arg;
	target_meals = program->nb_meals * program->nb_philos;
	while (1)
	{
		i = -1;
		total_meals = 0;
		while (++i < program->nb_philos)
		{
			pthread_mutex_lock(&program->philos[i].meal_mutex);
			total_meals += program->philos[i].nb_meals;
			pthread_mutex_unlock(&program->philos[i].meal_mutex);
			if (total_meals == target_meals || check_philo_died(& program->philos[i]))
			{
				set_death_lock(program);
				return (NULL);
			}
		}
		ft_usleep(10);
	}
	return (NULL);
}
