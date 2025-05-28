/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:39:10 by istripol          #+#    #+#             */
/*   Updated: 2025/05/28 19:21:44 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_timestamp(char *message, t_philo *philo)
{
	long long	now;
	t_bool		foo_died;

	pthread_mutex_lock(philo->dead_lock);
	foo_died = philo->program->foo_died;
	pthread_mutex_unlock(philo->dead_lock);
	if (foo_died == 1)
		return ;
	now = get_time_ms();
	pthread_mutex_lock(philo->write_lock);
	printf(BOLD"%lli"RESET CYAN" %i"RESET"%s", now, philo->id, message);
	pthread_mutex_unlock(philo->write_lock);
}

int	main(int ac, char **av)
{
	t_program		program;
	int long long	now;
	int				i;

	if (!(ac == 5 || ac == 6) || check_and_init(&av[1], &program) != 1)
		exit(0);
	now = get_time_ms();
	printf(CYAN"Timestamp start " BOLD"%lli\n"RESET, now);
	pthread_create(&program.monitor, NULL, monitor_thread, & program);
	start_philos(&program);
	i = 0;
	while (i < program.nb_philos)
		pthread_join(program.philos[i++].thread, NULL);
	pthread_join(program.monitor, NULL);
	ft_exit(&program, ERREXIT);
	return (0);
}
