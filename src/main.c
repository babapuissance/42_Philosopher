/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:15:30 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 17:51:56 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	destroy_mutexes(t_rules *r)
{
	int	i;

	if (!r || !r->forks)
		return ;
	i = 0;
	while (i < r->num_philos)
	{
		pthread_mutex_destroy(&r->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&r->print_lock);
	pthread_mutex_destroy(&r->meal_lock);
	pthread_mutex_destroy(&r->state_lock);
}

static void	free_arrays(t_rules *r)
{
	if (!r)
		return ;
	if (r->forks)
		free(r->forks);
	if (r->philos)
		free(r->philos);
}

static int	setup_rules(t_rules *r, int ac, char **av)
{
	memset(r, 0, sizeof(*r));
	if (parse_args(ac, av, r))
		return (error_msg("invalid argument"));
	if (init_philos(r))
		return (error_msg("init_philos failed"));
	if (init_mutex(r))
		return (error_msg("init_mutex failed"));
	return (0);
}

static int	start_and_join(t_rules *r)
{
	int	i;

	if (start_philos(r))
		return (error_msg("thread creation failed"));
	i = 0;
	while (i < r->num_philos)
	{
		pthread_join(r->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(r->monitor, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (setup_rules(&rules, ac, av))
	{
		destroy_mutexes(&rules);
		free_arrays(&rules);
		return (1);
	}
	if (start_and_join(&rules))
	{
		destroy_mutexes(&rules);
		free_arrays(&rules);
		return (1);
	}
	destroy_mutexes(&rules);
	free_arrays(&rules);
	return (0);
}
