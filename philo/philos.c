/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:22:33 by istripol          #+#    #+#             */
/*   Updated: 2025/05/29 19:02:52 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_philos(t_program *program)
{
	int	i;

	i = 0;
	program->started = get_time_ms();
	while (i < program->nb_philos)
	{
		if (pthread_create(& (program->philos[i].thread), NULL, \
			start_routine, & program->philos[i]))
			ft_exit(program, ERREXIT);
		i++;
	}
}

t_philo	*init_philos(t_program *program)
{
	int	i;

	i = 0;
	program->philos = malloc(sizeof(t_philo) * program->nb_philos);
	if (!program->philos)
		exit(0);
	while (i < program->nb_philos)
	{
		program->philos[i].simulation_start = & program->simulation_start;
		program->philos[i].id = i + 1;
		program->philos[i].time_to_sleep = program->time_to_sleep;
		program->philos[i].time_to_eat = program->time_to_eat;
		program->philos[i].time_to_die = program->time_to_die;
		program->philos[i].right_fork = NULL;
		program->philos[i].left_fork = NULL;
		program->philos[i].last_meal = program->started;
		program->philos[i].write_lock = &(program->write_lock);
		program->philos[i].dead_lock = &(program->dead_lock);
		program->philos[i].program = program;
		program->philos[i].nb_meals = 0;
		program->philos[i].max_meals = program->nb_meals;
		pthread_mutex_init(&(program->philos[i].meal_mutex), NULL);
		i++;
	}
	return (program->philos);
}

t_fork	*init_forks(t_program *program, t_philo *philos)
{
	int		i;

	program->forks = malloc(sizeof(t_fork) * program->nb_philos);
	if (!program->forks)
		ft_exit(program, ERRFORKS);
	i = 0;
	while (i < program->nb_philos)
	{
		program->forks[i].id = i + 1;
		if (pthread_mutex_init(& (program->forks[i].mutex), NULL) != 0)
			ft_exit(program, ERREXIT);
		i++;
	}
	i = 0;
	while (i < program->nb_philos)
	{
		philos[i].right_fork = & program->forks[philos[i].id - 1];
		if (program->nb_philos > 1)
			philos[i].left_fork = &\
			program->forks[(philos[i].id) % program->nb_philos];
		i++;
	}
	return (program->forks);
}

t_bool	check_and_init(char **args, t_program *program)
{
	int	i;

	i = 0;
	while (args[i])
		if (!is_number(args[i++]))
			return (0);
	program->simulation_start = 0;
	program->foo_died = 0;
	program->nb_philos = ft_atoi(args[0]);
	program->time_to_die = ft_atoi(args[1]);
	program->time_to_eat = ft_atoi(args[2]);
	program->time_to_sleep = ft_atoi(args[3]);
	program->nb_meals = 0;
	if (i == 5)
		program->nb_meals = ft_atoi(args[4]);
	if ((i == 5 && program->nb_meals <= 0)
		|| program->nb_philos > 200)
		return (0);
	pthread_mutex_init(&(program->write_lock), NULL);
	pthread_mutex_init(&(program->dead_lock), NULL);
	program->started = get_time_ms();
	program->philos = init_philos(program);
	program->forks = init_forks(program, program->philos);
	return (1);
}
