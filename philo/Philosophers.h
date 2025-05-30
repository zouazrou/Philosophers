/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:04 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/30 23:25:24 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#define	UNAVAILABLE -42
#define	US 1000

typedef long long ms_t;
// Like prototype funtion
typedef struct data_s data_t;

typedef struct      philo_s
{
	int				id;					// ok
	int				num_meals;					// ok
	ms_t			last_meal;			// ok
	pthread_mutex_t	meal_mutex;			// ok init loop
    pthread_mutex_t	*r_fork;			// ok
    pthread_mutex_t	*l_fork;			// ok
	data_t			*data;				// ok   search
}                   philo_t;








typedef struct      data_s
{
    int             num_ph;   			// ok
    ms_t		t_die;    			// ok
    ms_t		t_eat;  			// ok
    ms_t		t_sleep;  			// ok
    int				n_times_eat;  		// ok
    philo_t			*philosopher;		// ok
	pthread_mutex_t	*forks;				// ok declare & init loop
	pthread_mutex_t	display;  			// ok init
	pthread_mutex_t	simulation_mutex;	// ok init
	bool			simulation;			// ok
}					data_t;







// fetch data from shared resource
bool		simulation_is_stop(data_t *data);
int			get_num_meals(philo_t *philo);

// utils
ms_t		get_time(void);
ms_t	ft_atoi_plus(const char *nptr);
void		ft_putendl_fd(char *s, int fd);
void		display(char *str, philo_t *philo);

// routine
void		eating(philo_t *philo);
void		thinking(philo_t *philo);
void		sleeping(philo_t *philo);
void		use_left(philo_t *philo);
void		use_right(philo_t *philo);
void		*philosopher_life(void *arg);
void		*single_philosopher(void *arg);

// main functions
void		stop_simulation(data_t *data);
ms_t		time_simulation(void);
bool		is_die(philo_t *philo);
void		observer(data_t	*data);
void		allocate_initial(data_t *data);
void		clean_all_resource(data_t *data, pthread_t **ids);
void		handling_args(data_t *data, pthread_t **ph_ids, int ac, char **av);

#endif
