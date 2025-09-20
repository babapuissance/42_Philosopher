/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:15:30 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 00:08:01 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	pick_forks(const t_philo *ph, pthread_mutex_t **first, pthread_mutex_t **second)
{
	int left;
	int right;
	int even;

	left = ph->left_fork;
	right = ph->right_fork;
	even = (ph->id % 2 == 0);

	if (even)
	{
		*first = &ph->rules->forks[right];
		*second = &ph->rules->forks[left];
	}
	else
	{
		*first = &ph->rules->forks[left];
		*second = &ph->rules->forks[right];
	}
}

void	philo_eat(t_philo *ph)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	pick_forks(ph, &first, &second);

	pthread_mutex_lock(first);
	print_status(ph, "has taken a fork");
	pthread_mutex_lock(second);
	print_status(ph, "has taken a fork");

	print_status(ph, "is eating");
	update_last_meal(ph, current_time_ms());
	update_count_eat(ph, get_count_eat(ph) + 1);

	ft_usleep(ph->rules->time_to_eat, ph);

	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

void	philo_sleep(t_philo *ph)
{
	print_status(ph, "is sleeping");
	ft_usleep(ph->rules->time_to_sleep, ph);
}

void	philo_think(t_philo *ph)
{
	long long	now;
	long long	since_last;
	long long	ttd_left;
	long long	plan;

	now = current_time_ms();
	since_last = now - get_last_meal(ph);
	ttd_left = ph->rules->time_to_die - since_last - 10;
	if (ttd_left < 0)
		ttd_left = 0;
	plan = 50 + (ph->id * 37 + (now % 100)) % 150;
	if (plan > ttd_left)
		plan = ttd_left;

	print_status(ph, "is thinking");
	if (ttd_left > 20)
		ft_usleep(plan, ph);
}
