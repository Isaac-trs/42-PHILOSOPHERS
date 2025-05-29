/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:20:58 by istripol          #+#    #+#             */
/*   Updated: 2025/05/29 23:17:34 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_philosophers(t_program *program )
{
	int	i;

	print_success("ALL PHILOS");
	i = 0;
	printf(YELLOW"program->nb_philos : %i\n"RESET, program->nb_philos);
	while (i < program->nb_philos)
	{
		printf("-----------\n");
		printf(CYAN"Philo %i "RESET, program->philos[i].id);
		printf("right_fork -> "GREEN"%i (%p) "RESET \
			"| left_fork -> "RED"%i (%p)\n"RESET, \
			program->philos[i].right_fork->id, program->philos[i].right_fork, \
			program->philos[i].left_fork->id, program->philos[i].left_fork);
		printf("-----------\n");
		i++;
	}
}

void	print_program(t_program *program)
{
	print_success("PROGRAM");
	printf("philos-> %i | ttd -> %u | tte-> %i | tts-> %i | meals-> %i\n", \
		program->nb_philos, program->time_to_die, program->time_to_eat, \
		program->time_to_sleep, program->nb_meals);
}

void	print_success(char *word)
{
	unsigned int	i;

	i = 0;
	printf(" ");
	while (i++ < ft_strlen(word) + 17)
		printf(GREEN"-"RESET);
	printf(GREEN"\n| %s HAVE BEEN INIT |\n "RESET, word);
	while (i-- > 1)
		printf(GREEN"-"RESET);
	printf("\n");
}
