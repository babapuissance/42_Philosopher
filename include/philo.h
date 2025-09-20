/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:20:15 by nbariol-          #+#    #+#             */
/*   Updated: 2025/09/20 00:08:01 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_t		thread_id;
	struct s_rules	*rules;
}				t_philo;

typedef struct s_rules
{
	int				num_philos;
	int				must_eat_count;
	int				philo_is_dead_rip;
	int				print_blocked;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		start_time;
	int				all_ate;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	state_lock;
	t_philo			*philos;
}				t_rules;

/*parsing*/
int			parse_args(int ac, char **av, t_rules *rules);

/*init*/
int			init_philos(t_rules *rules);
int			init_mutex(t_rules *rules);
int			init_forks(t_rules *rules);

/*start_philos*/
int			start_philos(t_rules *rules);

/*philosopher*/
void		*philo_routine(void *arg);
void		philo_think(t_philo *ph);
void		philo_eat(t_philo *ph);
void		philo_sleep(t_philo *ph);

/*monitor.c*/
void		*monitor_philos(void *arg);

/*utils*/
long long	current_time_ms(void);
int			error_msg(const char *msg);
int			ft_usleep(int millisecondes, t_philo *ph);
void		print_status(t_philo *ph, char *msg);
int			check_state(t_philo *ph);

/*mutex wrappers*/
long long	get_last_meal(t_philo *ph);
void		update_last_meal(t_philo *ph, long long new_value);
int			get_count_eat(t_philo *ph);
void		update_count_eat(t_philo *ph, int new_value);
int			get_state_end(t_rules *rules);
void		update_state_end(t_rules *rules, int new_value);

# define RED    "\033[31m"
# define GREEN  "\033[32m"
# define YELLOW "\033[33m"
# define BLUE   "\033[34m"
# define RESET  "\033[0m"

#endif
