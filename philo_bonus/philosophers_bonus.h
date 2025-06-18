/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:04 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 19:05:18 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define UNAVAILABLE -42
# define US 1000

/*---Semaphore Names---*/
# define SEM_FORKS "/forks"
# define SEM_KILL "/kill"
# define SEM_WRITE "/write"
# define SEM_PH_COUNT "/ph_count"
# define SEM_MEAL "/meal_sem_"

typedef enum e_err
{
	NO_ERR,
	ARG,
	MALLOC,
	FORK,
	SEM_OPEN,
}						t_err;

typedef long long		t_ms;

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int		num_ph;
	t_ms	t_die;
	t_ms	t_eat;
	t_ms	t_sleep;
	int		n_times_eat;
	sem_t	*forks;
	sem_t	*kill;
	sem_t	*write;
	sem_t	*philos_done_eat;
	t_ms	start_time;
	t_philo	*philosopher;
	pid_t	*pid;
}						t_data;

typedef struct s_philo
{
	int		id;
	int		num_meals;
	t_ms	last_meal;
	sem_t	*sem_meal;
	t_data	*data;
}	t_philo;

// fetch data from shared resource
bool					valid_num_meals(t_philo *philo);
int						fetch_num_meals(t_philo *philo);
t_ms					fetch_last_meal(t_philo *philo);
t_ms					get_time(void);
t_ms					time_simulation(t_data *data);

/***********utils***********/
char					*ft_strjoin(char const *s1, char const *s2);
t_ms					ft_atoi_plus(const char *nptr);
void					ft_putendl_fd(char *s, int fd);
size_t					ft_strlen(const char *str);
char					*ft_strdup(const char *s);
int						ft_isdigit(int c);
char					*ft_itoa(int n);

/***********routine***********/
void					*observer(void *arg);
void					eating(t_philo *philo);
void					thinking(t_philo *philo);
void					sleeping(t_philo *philo);
void					philosopher_life(t_philo *philo);

/***********functions***********/
void					display(char *str, t_philo *philo);
void					handling_args(t_data *data, int ac, char **av);
void					allocate_initial(t_data *data);
void					kill_process(t_data *data);
bool					is_die(t_philo *philo);
void					clean_all_resource(t_data *data, t_err err);

/***********processes functions***********/
void					create_process(t_data *data);
void					kill_process(t_data *data);
void					*check_meal_completion(void *arg);

/***********semaphore functions***********/
void					init_semaphores(t_data *data);
void					open_semaphores(t_data *data);
void					close_semaphores(t_data *data);
void					unlink_semaphore(t_data *data);
char					*generate_namesem(int index);

#endif
