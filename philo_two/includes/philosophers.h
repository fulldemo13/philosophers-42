/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 21:05:24 by fulldemo          #+#    #+#             */
/*   Updated: 2020/05/18 10:57:44 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

struct s_state;

typedef struct		s_philo
{
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
	int				cur_eat_count;
	uint64_t		start;
	int				over;
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
int					start_threads(t_state *state);
sem_t				*ft_sem_open(char const *name, int value);
char				*make_semaphore_name(char const *base, char *buffer,
					int position);
void				*monitor_count(void *state_v);
void				*routine(void *philo_v);
int					take_forks(t_philo *philo);
int					clean_forks(t_philo *philo);
int					eat(t_philo *philo);
void				display_message(t_philo *philo, char *state);

#endif
