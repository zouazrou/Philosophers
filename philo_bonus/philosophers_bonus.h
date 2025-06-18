/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:04 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 15:34:36 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

#include <string.h>
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
#define	SEM_PH_COUNT  "/ph_count"
#define	SEM_MEAL  "/meal_sem_"

typedef long long ms_t;

typedef enum e_err
{
	NO_ERR,
	MALLOC,
	FORK,
	SEM_OPEN,
	ARG,
}	t_err;

typedef	struct philo_s philo_t;

typedef struct      data_s
{
	int				num_ph;	//ok
	ms_t			t_die; // ok
	ms_t			t_eat; // ok
	ms_t			t_sleep; // ok
	int				n_times_eat; // ok
	sem_t			*forks; // ok
	sem_t			*kill; // ok
	sem_t			*write; // ok
	sem_t			*philos_done_eat; // ok
	ms_t			start_time; // ok
	/*********/
	philo_t			*philosopher; // malloc ok
	pid_t			*pid;			// malloc ok
}					data_t;

typedef struct      philo_s
{
	int				id; // ok
	int				num_meals; // sh ok
	ms_t			last_meal; // sh ok
	sem_t			*sem_meal; // ok
	data_t			*data; // ok
}                   philo_t;

// fetch data from shared resource
bool	valid_num_meals(philo_t *philo);
int		fetch_num_meals(philo_t *philo);
ms_t	fetch_last_meal(philo_t *philo);

// utils
ms_t		get_time(void);
ms_t		ft_atoi_plus(const char *nptr);
void		ft_putendl_fd(char *s, int fd);
void		display(char *str, philo_t *philo);
char		*generate_namesem(int index);

// routine
void		eating(philo_t *philo);
void		thinking(philo_t *philo);
void		sleeping(philo_t *philo);
void		philosopher_life(philo_t *philo);

// main functions
void		handling_args(data_t *data, int ac, char **av);
void		allocate_initial(data_t *data);
void		kill_process(data_t *data);

ms_t		time_simulation(data_t *data);
bool		is_die(philo_t *philo);
void		clean_all_resource(data_t *data, t_err err);
void		unlink_semaphore(data_t *data);
void	close_semaphores(data_t *data);

#endif
