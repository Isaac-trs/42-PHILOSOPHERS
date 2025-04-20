/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:39:57 by istripol          #+#    #+#             */
/*   Updated: 2025/04/16 07:39:55by istripol         ###   ########.fr       */
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
# define EATING 1
# define SLEEPING 2
# define THINKING 3

typedef unsigned int	t_bool;


typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		meal_mutex;

	struct s_program	*program;
	int					id;
	long long		last_meal; //(microseconds)
	unsigned int	nb_meals;
	unsigned int	nb_think;

	struct s_fork	*left_fork;
	struct s_fork	*right_fork;

	int 				time_to_eat;
	int					time_to_sleep;
	int					time_to_die;

	t_bool			thinking;
	t_bool			eating;
	t_bool			dead;

	// First philo's right fork is last's left fork
	// Last philo's left fork is first's right fork
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	unsigned int	id;
	//t_philo			*left_philo;
	//t_philo			*right_philo;

}	t_fork;

typedef struct s_program
{
	pthread_mutex_t	write_lock;	// printf - thread-safe
	
	pthread_mutex_t	dead_lock;	// if a philo dies lock
	t_bool			foo_died;	// if a philo dies var

	t_philo			*philos;	 // array
	t_fork			*forks;		//	array

	long long		started; //(microseconds)
	int				nb_philos;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			time_to_die;

}	t_program;

typedef enum e_flag
{
	eat,
	sleeep,
	think,
	forking,
	start,
	threadd,
	all,
	//fork,
	null,
	philosophers
}	t_flag;

// functions.c
void	print_timestamp(char *message, t_philo *philo);
int		ft_atoi(const char *nptr);
t_bool	is_number(char *str);
void	clean_exit(t_program *program, t_flag flag, int thread);
long long	get_time_ms();

// debug.c
void	print_philosophers(t_program *programs);
void	print_success(char *word);

// philos.c
void	start_philos(t_program *program);
void	*start_routine(void *philo);

// routine.c
void	*monitor_thread(void *arg);
#endif
