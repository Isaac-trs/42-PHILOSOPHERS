/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:39:57 by istripol          #+#    #+#             */
/*   Updated: 2025/03/12 15:16:38 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define CYAN "\033[0;96m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

enum e_bool
{
	true,
	false,
};
typedef enum e_bool t_bool;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	meals;
	
	t_bool			eating;
	t_bool			dead;
} t_philo ;

typedef struct s_program
{
	t_philo *philos;
	
} t_program ;
#endif
