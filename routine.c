/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:29:36 by istripol          #+#    #+#             */
/*   Updated: 2025/05/09 08:58:15y istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	lock_forks(void *philo)
{
	
	// if (((t_philo *)philo)->left_fork->id > ((t_philo *)philo)->right_fork->id)
	if (((t_philo *)philo)->id % 2 == 0)
	{
		pthread_mutex_lock(&((t_philo *)philo)->right_fork->mutex);
		print_timestamp(ORANGE" has taken a fork\n"RESET, ((t_philo *)philo));
		// printf(RED"%i\n"RESET, ((t_philo *)philo)->left_fork->id);
		pthread_mutex_lock(&((t_philo *)philo)->left_fork->mutex);
		print_timestamp(ORANGE" has taken a fork\n"RESET, ((t_philo *)philo));
		// printf(GREEN"%i\n"RESET, ((t_philo *)philo)->right_fork->id);
	}
	else
	{
		pthread_mutex_lock(&((t_philo *)philo)->left_fork->mutex);
		print_timestamp(ORANGE" has taken a fork \n"RESET, ((t_philo *)philo));
		// printf(GREEN"%i\n"RESET, ((t_philo *)philo)->right_fork->id);
		pthread_mutex_lock(&((t_philo *)philo)->right_fork->mutex);
		print_timestamp(ORANGE" has taken a fork \n"RESET, ((t_philo *)philo));
		// printf(RED"%i\n"RESET, ((t_philo *)philo)->left_fork->id);
	}
}

static void	unlock_forks(void *philo)
{
	// if (((t_philo *)philo)->left_fork->id > ((t_philo *)philo)->right_fork->id)
	if (((t_philo *)philo)->id % 2 == 0)
	{
		pthread_mutex_unlock(&((t_philo *)philo)->right_fork->mutex);
		// print_timestamp(ORANGE" has dropped fork\n"RESET, ((t_philo *)philo));
		// printf(RED"%i\n"RESET, ((t_philo *)philo)->left_fork->id);
		pthread_mutex_unlock(&((t_philo *)philo)->left_fork->mutex);
		// print_timestamp(ORANGE" has dropped a fork\n"RESET, ((t_philo *)philo));
		// printf(GREEN"%i\n"RESET, ((t_philo *)philo)->right_fork->id);
	}
	else
	{
		pthread_mutex_unlock(&((t_philo *)philo)->left_fork->mutex);
		// print_timestamp(ORANGE" has dropped a fork \n"RESET, ((t_philo *)philo));
		// printf(GREEN"%i\n"RESET, ((t_philo *)philo)->right_fork->id);
		pthread_mutex_unlock(&((t_philo *)philo)->right_fork->mutex);
		// print_timestamp(ORANGE" has dropped a fork \n"RESET, ((t_philo *)philo));
		// printf(RED"%i\n"RESET, ((t_philo *)philo)->left_fork->id);
	}
}

void	*eating(void *phil)
{
	t_philo *philo;
	philo  = (t_philo *)phil;
	
	pthread_mutex_lock(& philo->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->nb_meals++;
	pthread_mutex_unlock(& philo->meal_mutex);
	lock_forks(philo);
	// t_program	*test = (t_program *)program;
	// printf("%li "CYAN BOLD"%ld"RESET YELLOW" is eating\n"RESET, time(NULL), pthread_self());
	print_timestamp(YELLOW" is eating\n"RESET, philo);
	// usleep(((t_philo *)philo)->time_to_eat * 1000);
	ft_usleep(philo->time_to_eat);
	

	// printf("| Philo %i last meal at "RED"%li"RESET"|\n", ((t_philo *)philo)->id, ((t_philo *)philo)->last_meal.tv_usec);
	// print_timestamp(ORANGE" unlocked forks "RESET, (t_philo *)philo);
	// printf(GREEN"%i & %i\n"RESET, ((t_philo *)philo)->right_fork->id, ((t_philo *)philo)->left_fork->id);
	
	// pthread_mutex_unlock(& philo->left_fork->mutex);
	// pthread_mutex_unlock(& philo->right_fork->mutex);
	unlock_forks(philo);
	print_timestamp(GREEN" finished eating\n"RESET, philo);

	// pthread_mutex_lock(& philo->meal_mutex);
	// philo->last_meal = get_time_ms();
	// philo->nb_meals++;
	// pthread_mutex_unlock(& philo->meal_mutex);
	
	// printf("Last meal of Philo %i: %li.%li\n", ((t_philo *)philo)->id, ((t_philo *)philo)->last_meal.tv_sec, ((t_philo *)philo)->last_meal.tv_usec);
	return NULL;
}

void	*sleeping(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	print_timestamp(YELLOW" is sleeping\n"RESET, philo);
	// printf("%li "CYAN BOLD"Philosopher %i"RESET YELLOW" is sleeping\n"RESET, time(NULL), ((t_philo *)philo)->id);
	ft_usleep(philo->time_to_sleep);
	
	print_timestamp(GREEN" finished sleeping\n"RESET, philo);
	return NULL;
}

t_bool	check_death_lock(t_program *program)
{
	t_bool	died;

	// pthread_mutex_lock(&program->dead_lock);
	died = program->foo_died;
	// pthread_mutex_unlock(&program->dead_lock);
	return (died);
}

void	*start_routine(void *philo)
{
	// print_timestamp("started routine\n", ((t_philo *)philo));
	// int i = 0;
	if ( ((t_philo *)philo)->id % 2 != 0)
		ft_usleep(1);
	((t_philo *)philo)->last_meal = get_time_ms();

	// while (((t_philo *)philo)->program->foo_died == 0)
	// {
		
	// 	if ( ((t_philo *)philo)->id % 2 != 0)
	// 	{
	// 		print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
	// 		if (check_death_lock(((t_philo *)philo)->program) == 1)
	// 			break;
	// 		sleeping((t_philo *)philo);
	// 		ft_usleep(1);
	// 		// check death
	// 		print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
	// 		// check death
	// 		if (check_death_lock(((t_philo *)philo)->program) == 1)
	// 			break;
	// 		eating((t_philo *)philo);
	// 	}
	// 	else
	// 	{
	// 		print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
	// 		if (check_death_lock(((t_philo *)philo)->program) == 1)
	// 			break;
	// 		eating((t_philo *)philo);
	// 		print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
	// 		if (check_death_lock(((t_philo *)philo)->program) == 1)
	// 			break;
	// 		sleeping((t_philo *)philo);
	// 		ft_usleep(1);
	// 	}
	// 	// if (i++ == 3)
	// 	// {
	// 		// pthread_mutex_lock(((t_philo *)philo)->dead_lock);
	// 		// ((t_philo *)philo)->program->foo_died = 1;
	// 		// pthread_mutex_unlock(((t_philo *)philo)->dead_lock);
	// 	// }
	// 	// usleep(1);
	// }
	// ----------------------------------------------------------------
	while (((t_philo *)philo)->program->foo_died == 0)
	{
		
		if ( ((t_philo *)philo)->id % 2 != 0)
		{
			if (check_death_lock(((t_philo *)philo)->program) == 1)
				break;
			sleeping((t_philo *)philo);
			if (check_death_lock(((t_philo *)philo)->program) == 1)
				break;
			// ft_usleep(1);
			// check death
			print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
			// check death
			if (check_death_lock(((t_philo *)philo)->program) == 1)
				break;
			eating((t_philo *)philo);
		}
		else
		{
			print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
			if (check_death_lock(((t_philo *)philo)->program) == 1)
				break;
			eating((t_philo *)philo);
			if (check_death_lock(((t_philo *)philo)->program) == 1)
				break;
			print_timestamp(YELLOW" is thinking\n"RESET, ((t_philo *)philo));
			if (check_death_lock(((t_philo *)philo)->program) == 1)
				break;
			sleeping((t_philo *)philo);
			if (check_death_lock(((t_philo *)philo)->program) == 1)
				break;
			// ft_usleep(1);
		}
	}
	// ----------------------------------------------------------------
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

static t_bool	check_philo_died(t_philo	*philo)
{
	long elapsed_meal;
	
	pthread_mutex_lock(& philo->meal_mutex);
	elapsed_meal = get_time_ms() - philo->last_meal;
	pthread_mutex_unlock(& philo->meal_mutex);

	if (elapsed_meal >= philo->time_to_die) // opposite for checks
	{
		pthread_mutex_lock(philo->dead_lock);
		philo->program->foo_died = 1;
		pthread_mutex_unlock(philo->dead_lock);

		//--------------------------------------------------------
		// pthread_mutex_lock(philo->write_lock);
		// printf(RED"LA\n"RESET);
		// pthread_mutex_unlock(philo->write_lock);
		// -------------------------------------------------------
		pthread_mutex_lock(philo->write_lock);
		printf(BOLD"%lli "RESET, get_time_ms());
		printf("Philo %i "RED"DIED\n"RESET, philo->id);
		printf("elapsed meal from philo %i %li\n", philo->id, elapsed_meal);

		pthread_mutex_unlock(philo->write_lock);
		return (1);
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_program	*program;
	int	i;

	program = (t_program *)arg;

	// pthread_mutex_lock(& program->write_lock);
	// printf(BOLD"MONITOR STARTED\n"RESET);
	// pthread_mutex_unlock(& program->write_lock);

	while (program->foo_died == 0)
	{
		i = -1;
		while (++i < program->nb_philos)
		{		
			if(check_philo_died(& program->philos[i]))
			{
				pthread_mutex_lock(& program->dead_lock);
				program->foo_died = 1;
				pthread_mutex_unlock(& program->dead_lock);
				
				// pthread_mutex_lock(& program->write_lock);
				// printf(BOLD"MONITOR STOPPED\n"RESET);
				// pthread_mutex_unlock(& program->write_lock);
				// pthread_mutex_destroy(& program->write_lock);
				// clean_exit(program, threadd, 0);
				// exit(0);

				return (NULL);
			}
		}
		ft_usleep(10);
	}
	// clean_exit(program, all, 1);
	return (NULL);
}