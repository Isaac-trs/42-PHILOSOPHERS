/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:39:10 by istripol          #+#    #+#             */
/*   Updated: 2025/05/30 00:02:33 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_timestamp(char *message, t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	if (check_death_lock(philo->program) == 1)
	{
		pthread_mutex_unlock(philo->write_lock);
		return ;
	}
	printf(BOLD"%lli"RESET CYAN" %i"RESET"%s", \
		get_time_ms() - philo->program->started, philo->id, message);
	pthread_mutex_unlock(philo->write_lock);
}

int	main(int ac, char **av)
{
	t_program		program;
	int				i;

	if (!(ac == 5 || ac == 6) || check_and_init(&av[1], &program) != 1)
		exit(0);
	pthread_create(&program.monitor, NULL, monitor_thread, & program);
	start_philos(&program);
	i = 0;
	while (i < program.nb_philos)
		pthread_join(program.philos[i++].thread, NULL);
	pthread_join(program.monitor, NULL);
	ft_exit(&program, ERREXIT);
	return (0);
}
