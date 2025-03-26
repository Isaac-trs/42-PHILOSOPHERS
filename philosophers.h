/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:39:57 by istripol          #+#    #+#             */
/*   Updated: 2025/03/26 09:28:18 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define ORANGE "\033[38;5;208m"
# define CYAN "\033[0;96m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

// STATES
#define EATING 1
#define SLEEPING 2
#define THINKING 3

typedef unsigned int t_bool;


typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	long int		started; //(microseconds)
	struct	timeval	tv;
	struct	timeval	last_meal; //(microseconds)
	long int		last_think; //(microseconds)
	unsigned int	nb_meals;
	unsigned int	nb_think;

	struct s_fork			*left_fork;
	struct s_fork			*right_fork;
	
	int		time_to_eat;
	int		time_to_sleep;
	int		time_to_die;
	
	t_bool			thinking;
	t_bool			eating;
	t_bool			dead;
	
	// First philo's right fork is last's left fork
	// Last philo's left fork is first's right fork
} t_philo ;

typedef struct	s_fork
{
	pthread_mutex_t	mutex;
	unsigned int	id;
	//t_philo			*left_philo;
	//t_philo			*right_philo;
	
	
} t_fork;

typedef struct s_program
{
	t_philo *philos;
	t_fork *forks;
	
	int	nb_philos;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_die;
	
	t_bool	alive;
	t_philo *died;

	
} t_program ;

typedef enum e_flag
{
	eat, sleeep, think, forking, start
} t_flag;

// functions.c
void	print_timestamp(char *message, t_philo *philo);
int		ft_atoi(const char *nptr);
t_bool	is_number(char *str);

// debug.c
void    print_philosophers(t_program *programs);
void    print_success(char *word);
#endif
