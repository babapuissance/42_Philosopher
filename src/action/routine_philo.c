/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:54:45 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 17:57:50 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* petit décalage pour les IDs pairs, évite le rush initial */
static void	delay_pair_offset(t_philo *ph)
{
	if ((ph->id & 1) == 0)
		ft_usleep(1, ph);
}

/* initialise le timestamp du dernier repas à l'entrée dans la routine */
static void	prime_last_meal(t_philo *ph)
{
	pthread_mutex_lock(&ph->rules->meal_lock);
	ph->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&ph->rules->meal_lock);
}

/* routine thread d’un philosophe (identique en comportement) */
void	*philo_routine(void *arg)
{
	t_philo		*ph;

	ph = (t_philo *)arg;
	delay_pair_offset(ph);
	prime_last_meal(ph);
	while (!check_state(ph))
	{
		philo_eat(ph);
		philo_sleep(ph);
		philo_think(ph);
	}
	return (NULL);
}
