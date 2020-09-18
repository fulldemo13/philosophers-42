/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 10:50:56 by fulldemo          #+#    #+#             */
/*   Updated: 2020/05/18 09:31:03 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

struct s_state;

typedef struct		s_philo
{
	pid_t			pid;
	int				position;
	int				is_eating;
	uint64_t		limit;
	uint64_t		last_eat;
	int				lfork;
	int				rfork;
	struct s_state	*state;
	int				eat_count;
	sem_t			*mutex;
	sem_t			*eat_count_m;
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
	sem_t			*forks_m;
	sem_t			*write_m;
	sem_t			*somebody_dead_m;
}					t_state;

void				ft_putchar(char c);
int					ft_strlen(char const *str);
int					ft_isdigit(int c);
int					ft_atoi(char const *str);
void				ft_putnbr(uint64_t n);
int					ft_strcpy(char *dst, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
uint64_t			get_time(void);
int					clear_state(t_state *state);
int					exit_error(char const *str);
int					init(t_state *state, int argc, char const **argv);
sem_t				*ft_sem_open(char const *name, int value);
char				*make_semaphore_name(char const *base, char *buffer,
				int position);
void				*monitor_count(void *state_v);
void				*monitor_life(void *philo_v);
int					routine(t_philo *philo_v);
int					start_monitor_thread(t_state *state);
int					start_process(t_state *state);
void				take_forks(t_philo *philo);
void				clean_forks(t_philo *philo);
void				eat(t_philo *philo);
void				display_message(t_philo *philo, char *state);

#endif
