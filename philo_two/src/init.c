/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 16:21:54 by fulldemo          #+#    #+#             */
/*   Updated: 2020/05/15 16:39:18 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

sem_t	*ft_sem_open(char const *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

void	init_semaphores(t_state *state)
{
	state->forks_m = ft_sem_open("SFork", state->amount);
	state->write_m = ft_sem_open("SWrite", 1);
	state->somebody_dead_m = ft_sem_open("SDead", 0);
}

int		start_threads(t_state *state)
{
	int			i;
	pthread_t	tid;
	void		*philo;

	if (state->must_eat_count > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_count, (void*)state) != 0)
			return (1);
		pthread_detach(tid);
	}
	state->start = get_time();
	i = 0;
	while (i < state->amount)
	{
		philo = (void*)(&state->philos[i]);
		if (pthread_create(&tid, NULL, &routine, philo) != 0)
			return (1);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}

void	init_philos(t_state *state)
{
	int		i;
	char	semaphore[250];

	i = 0;
	while (i < state->amount)
	{
		state->philos[i].is_eating = 0;
		state->philos[i].position = i;
		state->philos[i].lfork = i;
		state->philos[i].rfork = (i + 1) % state->amount;
		state->philos[i].eat_count = 0;
		state->philos[i].state = state;
		make_semaphore_name("SPhilo", (char*)semaphore, i);
		state->philos[i].mutex = ft_sem_open(semaphore, 1);
		make_semaphore_name("SEat", (char*)semaphore, i);
		state->philos[i].eat_count_m = ft_sem_open(semaphore, 0);
		i++;
	}
}

int		init(t_state *state, int argc, char const **argv)
{
	state->amount = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		state->must_eat_count = ft_atoi(argv[5]);
	else
		state->must_eat_count = 0;
	if (state->amount < 2 || state->amount > 200 || state->time_to_die < 60
		|| state->time_to_eat < 60 || state->time_to_sleep < 60
		|| state->must_eat_count < 0)
		return (1);
	state->forks_m = NULL;
	state->philos = NULL;
	state->cur_eat_count = 0;
	if (!(state->philos =
		(t_philo*)malloc(sizeof(*(state->philos)) * state->amount)))
		return (1);
	init_philos(state);
	init_semaphores(state);
	return (0);
}
