/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:30:45 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 00:08:01 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* cas particulier : un seul philosophe */
int	run_single_philo(t_rules *r)
{
	print_status(&r->philos[0], "has taken a fork");
	ft_usleep(r->time_to_die, &r->philos[0]);
	print_status(&r->philos[0], "died");
	return (0);
}

int	start_philos(t_rules *r)
{
	int	i;

	r->start_time = current_time_ms();
	if (r->num_philos == 1)
		return (run_single_philo(r));

	i = 0;
	while (i < r->num_philos)
	{
		if (pthread_create(&r->philos[i].thread_id, NULL,
				philo_routine, &r->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&r->monitor, NULL, monitor_philos, r) != 0)
		return (1);
	return (0);
}
