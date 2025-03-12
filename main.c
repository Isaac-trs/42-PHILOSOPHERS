/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:09:55 by istripol          #+#    #+#             */
/*   Updated: 2025/03/12 15:07:53 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eating(void *seconds)
{
	printf(BOLD"%ld"RESET YELLOW" is eating...\n"RESET, pthread_self());
	sleep(*(int *)seconds);
	printf(BOLD"%ld"RESET GREEN" finished eating\n"RESET, pthread_self());
	return NULL;
}

int	main()
{
	// if (!(ac == 5 || ac == 6))
	// {
	// 	printf(RED BOLD"Error: "RESET RED"Not enough args"RESET);
	// 	exit();
	// }
	// printf(av[0]);
	
	struct timeval tv;
	pthread_t thread;
	int	secs_main = 3;
	int secs_thread = 6;
	pthread_create(&thread, NULL, eating, &secs_thread);
	eating(&secs_main);

	if (gettimeofday(&tv, NULL) == 0 )
		printf(CYAN"Timestamp " BOLD"%li\n"RESET, tv.tv_sec);
	else
		perror(RED"Time failed\n"RESET);
	pthread_join(thread, NULL);
	return (0);
}
