/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:04 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/04 22:23:41 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

#define	UNAVAILABLE -42
#define	US 1000

/*---Semaphore Names---*/
#define	SEM_FORKS "/forks"
#define	SEM_KILL  "/kill"
#define	SEM_WRITE  "/write"
#define	SEM_PH_FULL  "/philos_are_full"
#define	SEM_MEAL  "/meal_sem_"

typedef long long ms_t;

typedef struct      data_s
{
	int				num_ph;	//ok
	ms_t			t_die; // ok
	ms_t			t_eat; // ok
	ms_t			t_sleep; // ok
	int				n_times_eat; // ok
	sem_t			*forks; // ok
	sem_t			*kill;
	sem_t			*write;
	sem_t			*philos_are_full;
	ms_t			start_time;
}					data_t;

typedef struct      philo_s
{
	int				id;
	int				num_meals; // sh
	ms_t			last_meal; // sh
	sem_t			*sem_meal;
	data_t			*data;
}                   philo_t;

// fetch data from shared resource
// bool		simulation_is_stop(data_t *data);
// int			get_num_meals(philo_t *philo);
bool	valid_num_meals(philo_t *philosopher);

// utils
ms_t		get_time(void);
ms_t		ft_atoi_plus(const char *nptr);
void		ft_putendl_fd(char *s, int fd);
void		display(char *str, philo_t *philo);
char		*generate_namesem(char *namesem, int   index);

// routine
void		eating(philo_t *philo);
void		thinking(philo_t *philo);
void		sleeping(philo_t *philo);
void		philosopher_life(philo_t *philosopher_life);
// void		*single_philosopher(void *arg);

// main functions
void		allocate_initial(philo_t **philosopher, data_t *data);
void		handling_args(data_t *data, pid_t **pid, int ac, char **av);
// char *generate_namesem(char *namesem, int index);

// void		stop_simulation(data_t *data);
ms_t		time_simulation(data_t *data);
bool		is_die(philo_t *philo);
// void		observer(data_t	*data);
void		clean_all_resource(data_t *data, philo_t **philosopher, pid_t **pid, int num_sem);
void		unlink_semaphore(int num);

#endif
