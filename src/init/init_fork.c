/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:29:33 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 17:58:18 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_forks(t_rules *r)
{
	int		i;

	if (!r)
		return (1);
	r->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* r->num_philos);
	if (!r->forks)
		return (1);
	i = 0;
	while (i < r->num_philos)
	{
		if (pthread_mutex_init(&r->forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&r->forks[i]);
			}
			free(r->forks);
			r->forks = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}
