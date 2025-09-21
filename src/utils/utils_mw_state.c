/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mw_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:20:45 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 18:00:03 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_state(t_philo *ph)
{
	return (get_state_end(ph->rules));
}

int	get_state_end(t_rules *rules)
{
	int	state;

	pthread_mutex_lock(&rules->state_lock);
	state = (rules->philo_is_dead_rip || rules->all_ate);
	pthread_mutex_unlock(&rules->state_lock);
	return (state);
}

void	update_state_end(t_rules *rules, int new_value)
{
	pthread_mutex_lock(&rules->state_lock);
	if (new_value == 1)
		rules->philo_is_dead_rip = 1;
	else if (new_value == 2)
		rules->all_ate = 1;
	pthread_mutex_unlock(&rules->state_lock);
}
