/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mw_count_eat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:20:45 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 17:59:53 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_count_eat(t_philo *ph)
{
	int	count;

	pthread_mutex_lock(&ph->rules->meal_lock);
	count = ph->meals_eaten;
	pthread_mutex_unlock(&ph->rules->meal_lock);
	return (count);
}

void	update_count_eat(t_philo *ph, int new_value)
{
	pthread_mutex_lock(&ph->rules->meal_lock);
	ph->meals_eaten = new_value;
	pthread_mutex_unlock(&ph->rules->meal_lock);
}
