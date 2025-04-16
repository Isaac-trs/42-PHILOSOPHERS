/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:29:36 by istripol          #+#    #+#             */
/*   Updated: 2025/04/16 08:40:06 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	lock_forks(void *philo)
{
	
	if (((t_philo *)philo)->left_fork->id > ((t_philo *)philo)->right_fork->id)
	{
		pthread_mutex_lock(&((t_philo *)philo)->left_fork->mutex);
		print_timestamp(ORANGE" has taken a fork\n"RESET, ((t_philo *)philo));
		// printf(RED"%i\n"RESET, ((t_philo *)philo)->left_fork->id);
		pthread_mutex_lock(&((t_philo *)philo)->right_fork->mutex);
		print_timestamp(ORANGE" has taken a fork\n"RESET, ((t_philo *)philo));
		// printf(GREEN"%i\n"RESET, ((t_philo *)philo)->right_fork->id);
	}
	else
	{
		pthread_mutex_lock(&((t_philo *)philo)->right_fork->mutex);
		print_timestamp(ORANGE" has taken a fork \n"RESET, ((t_philo *)philo));
		// printf(GREEN"%i\n"RESET, ((t_philo *)philo)->right_fork->id);
		pthread_mutex_lock(&((t_philo *)philo)->left_fork->mutex);
		print_timestamp(ORANGE" has taken a fork \n"RESET, ((t_philo *)philo));
		// printf(RED"%i\n"RESET, ((t_philo *)philo)->left_fork->id);
	}
}

static void	unlock_forks(void *philo)
{
	if (((t_philo *)philo)->left_fork->id > ((t_philo *)philo)->right_fork->id)
	{
		pthread_mutex_unlock(&((t_philo *)philo)->left_fork->mutex);
		// print_timestamp(ORANGE" has dropped fork\n"RESET, ((t_philo *)philo));
		// printf(RED"%i\n"RESET, ((t_philo *)philo)->left_fork->id);
		pthread_mutex_unlock(&((t_philo *)philo)->right_fork->mutex);
		// print_timestamp(ORANGE" has dropped a fork\n"RESET, ((t_philo *)philo));
		// printf(GREEN"%i\n"RESET, ((t_philo *)philo)->right_fork->id);
	}
	else
	{
		pthread_mutex_unlock(&((t_philo *)philo)->right_fork->mutex);
		// print_timestamp(ORANGE" has dropped a fork \n"RESET, ((t_philo *)philo));
		// printf(GREEN"%i\n"RESET, ((t_philo *)philo)->right_fork->id);
		pthread_mutex_unlock(&((t_philo *)philo)->left_fork->mutex);
		// print_timestamp(ORANGE" has dropped a fork \n"RESET, ((t_philo *)philo));
		// printf(RED"%i\n"RESET, ((t_philo *)philo)->left_fork->id);
	}
}

void	*eating(void *phil)
{
	t_philo *philo;
	philo  = (t_philo *)phil;
	
	lock_forks(philo);
	// t_program	*test = (t_program *)program;
	// printf("%li "CYAN BOLD"%ld"RESET YELLOW" is eating\n"RESET, time(NULL), pthread_self());
	print_timestamp(YELLOW" is eating\n"RESET, philo);
	// usleep(((t_philo *)philo)->time_to_eat * 1000);
	usleep(philo->time_to_eat * 1000);
	

	// printf("| Philo %i last meal at "RED"%li"RESET"|\n", ((t_philo *)philo)->id, ((t_philo *)philo)->last_meal.tv_usec);
	// print_timestamp(ORANGE" unlocked forks "RESET, (t_philo *)philo);
	// printf(GREEN"%i & %i\n"RESET, ((t_philo *)philo)->right_fork->id, ((t_philo *)philo)->left_fork->id);
	
	// pthread_mutex_unlock(& philo->left_fork->mutex);
	// pthread_mutex_unlock(& philo->right_fork->mutex);
	unlock_forks(philo);
	print_timestamp(GREEN" finished eating\n"RESET, philo);
	// gettimeofday(& philo->last_meal, NULL);
	philo->last_meal = get_time_ms();
	philo->nb_meals++;
	// printf("Last meal of Philo %i: %li.%li\n", ((t_philo *)philo)->id, ((t_philo *)philo)->last_meal.tv_sec, ((t_philo *)philo)->last_meal.tv_usec);
	return NULL;
}

void	*sleeping(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	print_timestamp(YELLOW" is sleeping\n"RESET, philo);
	// printf("%li "CYAN BOLD"Philosopher %i"RESET YELLOW" is sleeping\n"RESET, time(NULL), ((t_philo *)philo)->id);
	usleep(philo->time_to_sleep * 1000);
	
	print_timestamp(GREEN" finished sleeping\n"RESET, philo);
	return NULL;
}

void	*start_routine(void *philo)
{
	// print_timestamp("started routine\n", ((t_philo *)philo));
	// int i = 0;
	while (((t_philo *)philo)->program->foo_died == 0)
	{
		if ( ((t_philo *)philo)->id % 2 != 0)
		{
			print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
			sleeping((t_philo *)philo);
			// check death
			print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
			// check death
			eating((t_philo *)philo);
		}
		else
		{
			print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
			eating((t_philo *)philo);
			print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
			sleeping((t_philo *)philo);
		}
		// if (i++ == 3)
		// {
			// pthread_mutex_lock(((t_philo *)philo)->dead_lock);
			// ((t_philo *)philo)->program->foo_died = 1;
			// pthread_mutex_unlock(((t_philo *)philo)->dead_lock);
		// }
	}
	//clean_exit(((t_philo *)philo)->program, all, 0);
// 
	// int j = 0;
	// for (int i = 0; i<3; i++)
	// {
		// if ( ((t_philo *)philo)->id % 2 != 0)
		// {
			// print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
			// sleeping((t_philo *)philo);
			// print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
			// eating((t_philo *)philo);
			// j++;
			// if (j == 3)
				// break;
		// }
		// else
		// {
			// print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
			// eating((t_philo *)philo);
			// print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
			// sleeping((t_philo *)philo);
			// if (j == 3)
				// break;
			// j++;
		// }
		// clean_exit(((t_philo *)philo)->program, all, 0);
	// }
	
	// clean_exit(((t_philo *)philo)->program, all, 0);
	
	// if ( ((t_philo *)philo)->id % 2 != 0)
	// 	sleeping((t_philo *)philo);
	// else
	// 	eating((t_philo *)philo);

	return (int *)1;
}

void	*monitor_thread(void *arg)
{
	t_program	*program;
	t_philo		*philo;		
	long	elapsed_meal;
	int	i;

	program = (t_program *)arg;

	pthread_mutex_lock(& program->write_lock);
	printf(BOLD"MONITOR STARTED\n"RESET);
	pthread_mutex_unlock(& program->write_lock);

	i = -1;
	while (program->foo_died == 0)
	{
		i = -1;
		while (++i < program->nb_philos)
		{
			// pthread_mutex_lock(& program->write_lock);
			// printf(GREEN"ICI\n"RESET);
			// pthread_mutex_unlock(& program->write_lock);
			
			philo = & program->philos[i];
			pthread_mutex_lock(& philo->meal_mutex);
			elapsed_meal = get_time_ms() - philo->last_meal;
			pthread_mutex_unlock(& philo->meal_mutex);
			if (elapsed_meal < program->time_to_die) // opposite for checks
			{
				pthread_mutex_lock(& program->write_lock);
				printf(RED"LA\n"RESET);
				pthread_mutex_unlock(& program->write_lock);
				pthread_mutex_unlock(& philo->meal_mutex);
				
				pthread_mutex_lock(philo->dead_lock);
				philo->program->foo_died = 1;
				pthread_mutex_unlock(philo->dead_lock);
				print_timestamp(RED" DIED\n"RESET, philo);
				printf("elapsed meal from philo %i %li\n", philo->id, elapsed_meal);
				return NULL;
			}
			// pthread_mutex_unlock(& philo->meal_mutex);
		}
		usleep(1000); // CPU HOGGING ?
	}
	printf(BOLD"MONITOR ENDED"RESET);
	return NULL;
}