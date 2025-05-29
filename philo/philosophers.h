/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:39:57 by istripol          #+#    #+#             */
/*   Updated: 2025/05/29 23:20:19 by istripol         ###   ########.fr       */
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
# define ERRPHILO 1
# define ERRFORKS 2
# define ERREXIT  3
# define ERRARGS  4

typedef unsigned int	t_bool;

typedef struct s_philo
{
	t_bool				*simulation_start;
	pthread_t			thread;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		meal_mutex;

	struct s_program	*program;
	int					id;
	long long			last_meal;
	unsigned int		nb_meals;
	unsigned int		max_meals;

	struct s_fork		*left_fork;
	struct s_fork		*right_fork;

	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;

	t_bool				thinking;
	t_bool				eating;
	t_bool				dead;

}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	unsigned int	id;
	t_bool			in_use;
}	t_fork;

typedef struct s_program
{
	t_bool			simulation_start;
	pthread_mutex_t	write_lock;	
	pthread_mutex_t	dead_lock;	
	t_bool			foo_died;	
	t_philo			*philos;	
	t_fork			*forks;		
	pthread_t		monitor;
	long long		started;
	int				nb_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				nb_meals;
	unsigned int	target_meals;
}	t_program;

// main.c
void		print_timestamp(char *message, t_philo *philo);
// functions.c
int			ft_atoi(const char *nptr);
t_bool		is_number(char *str);
long long	get_time_ms(void);
void		ft_usleep(long ms);
void		ft_exit(t_program *program, int flag);
// debug.c
void		print_philosophers(t_program *programs);
void		print_success(char *word);
void		print_program(t_program *program);

// philos.c
void		start_philos(t_program *program);
t_philo		*init_philos(t_program *program);
t_bool		check_and_init(char **args, t_program *program);
t_fork		*init_forks(t_program *program, t_philo *philos);

// routine.c
void		*start_routine(void *philo);

// monitor.c
t_bool		check_death_lock(t_program *program);
void		*monitor_thread(void *arg);

#endif
