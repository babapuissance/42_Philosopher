/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:45:20 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 00:08:01 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	has_starved(t_philo *ph, long long now_ms)
{
	return ((now_ms - get_last_meal(ph)) > ph->rules->time_to_die);
}

static int	mark_dead_and_print(t_rules *rules, t_philo *ph)
{
	int already_flagged;

	pthread_mutex_lock(&rules->state_lock);
	already_flagged = rules->philo_is_dead_rip;
	pthread_mutex_unlock(&rules->state_lock);
	if (!already_flagged)
	{
		update_state_end(rules, 1);
		print_status(ph, "died");
	}
	return (1);
}

static int	scan_deaths(t_rules *rules)
{
	int			i;
	long long	now;

	now = current_time_ms();
	i = 0;
	while (i < rules->num_philos)
	{
		if (has_starved(&rules->philos[i], now))
			return (mark_dead_and_print(rules, &rules->philos[i]));
		++i;
	}
	return (0);
}

static int	everyone_met_quota(t_rules *rules)
{
	int i;
	int done;
	int quota;

	quota = rules->must_eat_count;
	if (quota <= 0)
		return (0);
	done = 0;
	i = 0;
	while (i < rules->num_philos)
	{
		if (get_count_eat(&rules->philos[i]) >= quota)
			++done;
		++i;
	}
	if (done == rules->num_philos)
	{
		update_state_end(rules, 2);
		return (1);
	}
	return (0);
}

void	*monitor_philos(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	while (1)
	{
		if (scan_deaths(rules))
			break ;
		if (everyone_met_quota(rules))
			break ;
		ft_usleep(1, NULL);
	}
	return (NULL);
}
