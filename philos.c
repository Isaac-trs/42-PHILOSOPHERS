/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:22:33 by istripol          #+#    #+#             */
/*   Updated: 2025/04/16 09:42:49 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_philos(t_program *program)
{
	int	i;
	
	i = 0;
	while (i < program->nb_philos)
	{
		// program->philos[i].started = get_time_ms();
		if (pthread_create(& (program->philos[i].thread), NULL, start_routine, & program->philos[i]))
			clean_exit(program, threadd, i);
		i++;
	}
	while (i > 0)
		pthread_join(program->philos[--i].thread, NULL);

}

