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


// void	*eating(void *miliseconds)
// void	*eating(void *program)
void	*eating(void *philo)
{
	// t_program	*test = (t_program *)program;
	// printf("%li "CYAN BOLD"%ld"RESET YELLOW" is eating\n"RESET, time(NULL), pthread_self());
	printf("%li "CYAN BOLD"Philosopher %i"RESET YELLOW" is eating\n"RESET, time(NULL), ((t_philo *)philo)->id);
	sleep(((t_philo *)philo)->time_to_eat);
	printf("%li "CYAN BOLD"Philosopher %i"RESET GREEN" finished eating\n"RESET, time(NULL), ((t_philo *)philo)->id);
	return NULL;
}

void	*thinking(void *philo)
{
	printf("%li "CYAN BOLD"Philosopher %i"RESET YELLOW" is thinking\n"RESET, time(NULL), ((t_philo *)philo)->id);
	// sleep(((t_philo *)philo)->time_to_think);
	printf("%li "CYAN BOLD"Philosopher %i"RESET GREEN" finished thinking\n"RESET, time(NULL), ((t_philo *)philo)->id);
	return NULL;
}

void	*sleeping(void *philo)
{
	printf("%li "CYAN BOLD"Philosopher %i"RESET YELLOW" is sleeping\n"RESET, time(NULL), ((t_philo *)philo)->id);
	sleep(((t_philo *)philo)->time_to_sleep);
	printf("%li "CYAN BOLD"Philosopher %i"RESET GREEN" finished sleeping\n"RESET, time(NULL), ((t_philo *)philo)->id);
	return NULL;
}

void	*start_routine(void *philo)
{

	if ( ((t_philo *)philo)->id % 2 != 0)
		sleeping((t_philo *)philo);
	else 
		eating((t_philo *)philo);

	return NULL;
}

t_philo	*init_philos(t_program *program)
{
	t_philo *philos;
	int	i;

	i = 0;
	philos = malloc(sizeof(t_philo) * program->nb_philos);
	if (!philos)
	{
		perror(RED"MALLOC PHILOS ERROR"RESET);
		exit(1);
	}
	while (i < program->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].time_to_sleep = program->time_to_sleep;
		philos[i].time_to_eat = program->time_to_eat;
		// philos[i].time_to_die = program->time_to_die;
		printf("Philo[%i] created | tte [%i] | tts [%i] | ttd [%i]\n", philos[i].id, philos[i].time_to_eat, philos[i].time_to_sleep, philos[i].time_to_die);
		i++;
	}
	return (philos);
}

t_fork *init_forks(unsigned int nb_philos, t_philo *philos)
{
	t_fork	*forks;
	unsigned int		i;

	forks = malloc(sizeof(t_fork) * nb_philos);
	if (!forks)
	{
		perror(RED"MALLOC FORKS ERROR"RESET);
		exit(1);
	}
	i = 0;
	while (i < nb_philos)
	{
		forks[i].id = i + 1;
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		//forks[i].id = i + 1;
		//forks[i].left_philo= &philos[i];
		philos[i].right_fork = &forks[philos[i].id - 1];
		philos[i].left_fork = &forks[(philos[i].id ) % nb_philos];
		printf("Philo[%i] | right_fork -> %i | left_fork -> %i\n", philos[i].id, philos[i].right_fork->id, philos[i].left_fork->id);
		//forks[i].right_philo = &philos[(  % nb_philos];
		//printf("fork[%i] created, left = philo[%i] | right = philo[%i] \n", forks[i].id, forks[i].left_philo->id, forks[i].right_philo->id);
		i++;
	}
	return (forks);

}

t_bool	check_and_init(char **args, t_program *program)
{
	int	i;

	i = 0;
	while (args[i]) 
		if (!is_number(args[i++]))
			return (0);
	program->nb_philos = ft_atoi(args[0]); 
	// program->time_to_die = ft_atoi(args[1]);
	program->time_to_eat = ft_atoi(args[1]);
	// program->time_to_sleep = ft_atoi(args[3]);
	 program->time_to_sleep = ft_atoi(args[2]);

	printf("%i %i %i %i\n", program->nb_philos, program->time_to_die, program->time_to_eat, program->time_to_sleep);
	program->philos = init_philos(program);
	program->forks = init_forks(program->nb_philos, program->philos);
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
	
	// struct timeval tv;
	// pthread_t thread;
	// int	secs_main = 3;
	// int secs_thread = 6;
	// pthread_create(&thread, NULL, eating, &secs_thread);
	// eating(&secs_main);

	// if (gettimeofday(&tv, NULL) == 0 )
	// 	printf(CYAN"Timestamp " BOLD"%li\n"RESET, tv.tv_sec);
	// else
	// 	perror(RED"Time failed\n"RESET);
	// pthread_join(thread, NULL);

	//pthread_t	*threads = malloc(sizeof(pthread_t)* ft_atoi(av[1]));

	check_and_init(&av[1], &program);

	// t_philo *philoss = malloc(sizeof(t_philo)* ft_atoi(av[1]));
	// if (!philoss)
	// {
	// 	perror(RED"MALLOC ERROR"RESET);
	// 	exit(1);
	// }
	
	 int i = 0;
	 while (i < program.nb_philos)
	{
		if (program.philos[i].id % 2 != 0 )
			// pthread_create(&(program.philos[i].thread), NULL, eating, &program.time_to_eat);
			pthread_create(&(program.philos[i].thread), NULL, start_routine, &program.philos[i]);
		else
			pthread_create(&(program.philos[i].thread), NULL, start_routine, &program.philos[i]);
		i++;
	}
	// i = 0;
	while (i > 0)
		pthread_join(program.philos[--i].thread, NULL);
	// free(philoss);


	return (0);
}
