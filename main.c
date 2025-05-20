/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:39:10 by istripol          #+#    #+#             */
/*   Updated: 2025/05/20 04:33:16 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:09:55 by istripol          #+#    #+#             */
/*   Updated: 2025/03/16 23:04:17by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philos(t_program *program)
{
	// t_philo *philos;
	int	i;

	i = 0;
	program->philos = malloc(sizeof(t_philo) * program->nb_philos);
	if (!program->philos)
		exit(1);
	while (i < program->nb_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].time_to_sleep = program->time_to_sleep;
		program->philos[i].time_to_eat = program->time_to_eat;
		program->philos[i].time_to_die = program->time_to_die;
		// program->philos[i].time_to_die = 66;
		program->philos[i].right_fork = NULL;
		program->philos[i].left_fork = NULL;
		program->philos[i].last_meal = program->started;
		program->philos[i].write_lock = &(program->write_lock);
		program->philos[i].dead_lock = &(program->dead_lock);
		program->philos[i].program = program;
		pthread_mutex_init(&(program->philos[i].meal_mutex), NULL);
		// printf("Philo[%i] created | tte [%i] | tts [%i] | ttd [%i]\n", philos[i].id, philos[i].time_to_eat, philos[i].time_to_sleep, philos[i].time_to_die);
		printf("Philo[%i] created | tte [%i] | tts [%i] | ttd [%i]\n", program->philos[i].id, program->philos[i].time_to_eat, program->philos[i].time_to_sleep, program->philos[i].time_to_die);
		i++;
	}
	print_success("ALL PHILOS");
	return (program->philos);
}

t_fork *init_forks(t_program *program, t_philo *philos)
{
	// t_fork	*forks;
	int		i;

	program->forks = malloc(sizeof(t_fork) * program->nb_philos);
	if (!program->forks)
		clean_exit(program, forking, 0);
	i = 0;
	while (i < program->nb_philos)
	{
		program->forks[i].id = i + 1;
		if (pthread_mutex_init(&(program->forks[i].mutex), NULL) != 0)
			clean_exit(program, null, 0);
		i++;
	}
	i = 0;
	while (i < program->nb_philos)
	{
		//forks[i].id = i + 1;
		//forks[i].left_philo= &philos[i];
		philos[i].right_fork = &program->forks[philos[i].id - 1];
		philos[i].left_fork = &program->forks[(philos[i].id ) % program->nb_philos];
		// printf("Philo[%i] | right_fork -> %i (%p) | left_fork -> %i (%p)\n", philos[i].id, philos[i].right_fork->id, philos[i].right_fork ,philos[i].left_fork->id, philos[i].left_fork);
		//forks[i].right_philo = &philos[(  % nb_philos];
		//printf("fork[%i] created, left = philo[%i] | right = philo[%i] \n", forks[i].id, forks[i].left_philo->id, forks[i].right_philo->id);
		i++;
	}
	
	print_success("ALL FORKS");
	print_philosophers(program);

	return (program->forks);

}

t_bool	check_and_init(char **args, t_program *program)
{
	int	i;

	i = 0;
	while (args[i]) 
		if (!is_number(args[i++]))
			return (0);
	pthread_mutex_init(&(program->write_lock), NULL);
	pthread_mutex_init(&(program->dead_lock), NULL);
	program->foo_died = 0;
	program->nb_philos = ft_atoi(args[0]); 
	// program->time_to_die = ft_atoi(args[1]);
	program->time_to_die = 410;
	program->time_to_eat = ft_atoi(args[1]);
	// program->time_to_sleep = ft_atoi(args[3]);
	program->time_to_sleep = ft_atoi(args[2]);

	printf("%i %i %i %i\n", program->nb_philos, program->time_to_die, program->time_to_eat, program->time_to_sleep);
	program->started = get_time_ms();
	program->philos = init_philos(program);
	program->forks = init_forks(program, program->philos);
	return (1);
}

int	main(int ac, char **av)
{
	t_program	program;
	// if (!(ac == 5 || ac == 6))
	if (ac != 3 && !is_number(av[1]))
		exit(0);
	// {
	// 	printf(RED BOLD"Error: "RESET RED"Not enough args"RESET);
	// 	exit();
	// }
	// printf(av[0]);
	

	check_and_init(&av[1], &program);

	pthread_t monitor;
	pthread_create(&monitor, NULL,  monitor_thread, & program);
	// pthread_join(monitor, NULL);
	
	long long now = get_time_ms();
	printf(CYAN"Timestamp start " BOLD"%lli\n"RESET, now);

	start_philos(&program);

	// free(philoss);

	for (int i = 0; i < program.nb_philos; i++)
		pthread_join(program.philos[i].thread, NULL);

	pthread_join(monitor, NULL);

	t_bool test;
	while (1)
	{
		pthread_mutex_lock(&program.dead_lock);
		test = program.foo_died;
		pthread_mutex_unlock(&program.dead_lock);
		if (test == 1)
			break;
	}
	clean_exit(&program, all, 0);



	return (0);
}
