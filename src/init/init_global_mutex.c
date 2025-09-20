/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:55:21 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 17:59:22 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* initialise les mutex globaux (print / meal / state) */
static int	init_global_mutexes(t_rules *r)
{
	if (pthread_mutex_init(&r->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&r->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&r->print_lock);
		return (1);
	}
	if (pthread_mutex_init(&r->state_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&r->meal_lock);
		pthread_mutex_destroy(&r->print_lock);
		return (1);
	}
	return (0);
}

/* détruit les mutex globaux (rollback) */
static void	destroy_global_mutexes(t_rules *r)
{
	pthread_mutex_destroy(&r->state_lock);
	pthread_mutex_destroy(&r->meal_lock);
	pthread_mutex_destroy(&r->print_lock);
}

/* initialise tous les mutex (globaux + forks) */
int	init_mutex(t_rules *r)
{
	if (!r)
		return (1);
	if (init_global_mutexes(r))
		return (1);
	if (init_forks(r))
	{
		destroy_global_mutexes(r);
		return (1);
	}
	return (0);
}
