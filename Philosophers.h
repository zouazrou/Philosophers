/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:04 by zouazrou          #+#    #+#             */
/*   Updated: 2025/04/15 10:18:32 by zouazrou         ###   ########.fr       */
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
#define	MS 1000

typedef long long ms_t;
// Like prototype funtion
typedef struct data_s data_t;

#define IS_ODD(num) (num % 2)

typedef struct      philo_s
{
	// pthread_t       th;					// ok
	int				id;					// ok
	ms_t			last_meal;			// ok
	pthread_mutex_t	meal_mutex;			// ok
    pthread_mutex_t	*r_fork;			// ok
    pthread_mutex_t	*l_fork;			// ok
	data_t			*data;				// ok   search
}                   philo_t;








typedef struct      data_s
{
    int             num_ph;   			// ok
    long long		t_die;    			// ok
    long long		t_eat;  			// ok
    long long		t_sleep;  			// ok
    int				num_meals;  		// ok
    philo_t			*philosopher;		// ok
	pthread_mutex_t	*forks;				// ok
	pthread_mutex_t	display;  			// ok
	pthread_mutex_t	simulation_mutex;	// ok
	bool			simulation;	// ok
}					data_t;





















// fetch data from shared resource
bool		simulation_stop(data_t *data);


// utils
long long	ft_atoi_plus(const char *nptr);
long long	get_time(void);
long long	time_simulation(void);
void		display(char *str, philo_t *philo);
void		clean_all_resource(data_t *data, pthread_t **ids);
void		observer(data_t	*data);
bool		is_odd(int id);

// main functions
void		handling_args(data_t *data, pthread_t **ph_ids, int ac, char **av);
void		allocate_initial(data_t *data);

#endif
