/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:04 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/17 19:09:28 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define UNAVAILABLE -42
# define US 1000

typedef long long		t_ms;
typedef struct data_s	t_data;

typedef enum e_err
{
	NO_ERR,
	MALLOC,
	MUTEX,
	ARG,
	EDGE,
}						t_err;

typedef struct philo_s
{
	int					id;
	int					num_meals;
	t_ms				last_meal;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	t_data				*data;
}						t_philo;

typedef struct data_s
{
	int					num_ph;
	t_ms				t_die;
	t_ms				t_eat;
	t_ms				t_sleep;
	int					n_times_eat;
	t_philo				*philosopher;
	pthread_mutex_t		*forks;
	pthread_mutex_t		display;
	pthread_mutex_t		simulation_mutex;
	bool				simulation;
	void				*addrs[3];
}						t_data;

// utils
bool					simulation_is_stop(t_data *data);
int						get_num_meals(t_philo *philo);
t_ms					get_time(void);
t_ms					ft_atoi_plus(const char *nptr);
void					ft_putendl_fd(char *s, int fd);
void					display(char *str, t_philo *philo);
void					stop_simulation(t_data *data);
t_ms					time_simulation(void);
void					err_msg(t_err type);

// routine functions
void					use_right(t_philo *philo);
void					use_left(t_philo *philo);
void					eating(t_philo *philo);
void					thinking(t_philo *philo);
void					sleeping(t_philo *philo);
void					use_left(t_philo *philo);
void					use_right(t_philo *philo);
void					*philosopher_life(void *arg);
void					*single_philosopher(void *arg);

// main functions
bool					is_die(t_philo *philo);
void					observer(t_data *data);
t_err					allocate_initial(t_data *data);
void					clean_all_resource(t_data *data, t_err err);
t_err					handling_args(t_data *data, pthread_t **ph_ids, int ac,
							char **av);

#endif
