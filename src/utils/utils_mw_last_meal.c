/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mw_last_meal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:20:45 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 18:02:07 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_last_meal(t_philo *ph)
{
	long long	last_meal;

	pthread_mutex_lock(&ph->rules->meal_lock);
	last_meal = ph->last_meal_time;
	pthread_mutex_unlock(&ph->rules->meal_lock);
	return (last_meal);
}

void	update_last_meal(t_philo *ph, long long new_value)
{
	pthread_mutex_lock(&ph->rules->meal_lock);
	ph->last_meal_time = new_value;
	pthread_mutex_unlock(&ph->rules->meal_lock);
}
