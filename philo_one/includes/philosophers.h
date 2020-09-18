/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 10:32:24 by fulldemo          #+#    #+#             */
/*   Updated: 2020/04/22 11:23:19 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct s_state;

typedef struct		s_philo
{
	int				position;
	int				is_eating;
	uint64_t		limit;
	uint64_t		last_eat;
	int				lfork;
	int				rfork;
	int				eat_count;
	struct s_state	*state;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_m;
}					t_philo;

typedef struct		s_state
{
	int				amount;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				must_eat_count;
	uint64_t		start;
	t_philo			*philos;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	somebody_dead_m;
}					t_state;

int					ft_strlen(char const *str);
int					ft_atoi(char const *str);
int					ft_isdigit(int c);
void				ft_putchar(char c);
int					ft_strcmp(const char *s1, const char *s2);
uint64_t			get_time(void);
int					clear_state(t_state *state);
int					exit_error(char const *str);
int					check_arguments(int argc, char const **argv);
void				ft_putnbr(uint64_t n);
int					init_mutexes(t_state *state);
void				init_philos(t_state *state);
int					init(t_state *state, int argc, char const **argv);
int					start_threads(t_state *state);
void				display_message(t_philo *philo, char *state);
void				philo_life(t_philo *philo);
void				*monitor_count(void *state_v);
void				*monitor_life(void *philo_v);
void				*start_life(void *philo_v);
#endif
