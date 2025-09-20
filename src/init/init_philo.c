/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:15:30 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 00:08:01 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void setup_one_philo(t_rules *r, int idx, long long start)
{
	t_philo *p = &r->philos[idx];

	p->id = idx + 1;
	if (idx + 1 == r->num_philos)
		p->right_fork = 0;
	else
		p->right_fork = idx + 1;
	p->left_fork = idx;
	p->last_meal_time = start;
	p->meals_eaten = 0;
	p->thread_id = (pthread_t)0;
	p->rules = r;
}

/* initialise le tableau de philosophes */
int init_philos(t_rules *rules)
{
	int i;
	long long start;

	if (!rules)
		return (1);
	start = current_time_ms();
	rules->start_time = start;
	rules->philos = (t_philo *)calloc((size_t)rules->num_philos, sizeof(t_philo));
	if (!rules->philos)
		return (1);
	i = 0;
	while (i < rules->num_philos)
	{
		setup_one_philo(rules, i, start);
		i++;
	}
	return (0);
}