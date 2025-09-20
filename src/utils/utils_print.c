/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:20:45 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 00:08:01 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->rules->print_lock);
	
	if (strcmp(msg, "died") == 0)
	{
		ph->rules->print_blocked = 1;
		printf("%lld %d %s\n",
			current_time_ms() - ph->rules->start_time, ph->id, msg);
	}
	else if (!ph->rules->print_blocked)
	{
		printf("%lld %d %s\n",
			current_time_ms() - ph->rules->start_time, ph->id, msg);
	}
	
	pthread_mutex_unlock(&ph->rules->print_lock);
}

int error_msg(const char *msg)
{
    fprintf(stderr,
        RED "Error: %s" RESET "\n— check: "
        YELLOW "./philo <number_of_philosophers> <time_to_die_ms> "
        "<time_to_eat_ms> <time_to_sleep_ms> [must_eat_count]\n" RESET,
        msg);
    return (1);
}