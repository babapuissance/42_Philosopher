/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:30:20 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 17:52:44 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	parse_pos_int(const char *s, int *out)
{
	long long	acc;
	int			seen;
	int			d;

	if (!s || !*s || !out)
		return (1);
	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		s++;
	if (*s == '+')
		s++;
	acc = 0;
	seen = 0;
	while (*s >= '0' && *s <= '9')
	{
		d = *s - '0';
		seen = 1;
		if (acc > (INT_MAX - d) / 10)
			return (1);
		acc = acc * 10 + d;
		s++;
	}
	if (*s != '\0' || !seen || acc <= 0)
		return (1);
	*out = (int)acc;
	return (0);
}

int	parse_args(int ac, char **av, t_rules *rules)
{
	if (!rules || (ac != 5 && ac != 6))
		return (1);
	if (parse_pos_int(av[1], &rules->num_philos))
		return (1);
	if (parse_pos_int(av[2], &rules->time_to_die))
		return (1);
	if (parse_pos_int(av[3], &rules->time_to_eat))
		return (1);
	if (parse_pos_int(av[4], &rules->time_to_sleep))
		return (1);
	if (ac == 6)
	{
		if (parse_pos_int(av[5], &rules->must_eat_count))
			return (1);
	}
	else
		rules->must_eat_count = -1;
	rules->philo_is_dead_rip = 0;
	rules->print_blocked = 0;
	rules->all_ate = 0;
	return (0);
}
