/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 17:10:38 by fulldemo          #+#    #+#             */
/*   Updated: 2020/05/18 09:28:08 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_semaphores(t_state *state)
{
	state->forks_m = ft_sem_open("SFork", state->amount);
	state->write_m = ft_sem_open("SWrite", 1);
	state->somebody_dead_m = ft_sem_open("SDead", 0);
}

int		start_monitor_thread(t_state *state)
{
	pthread_t	tid;

	if (state->must_eat_count > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_count, (void*)state) != 0)
			return (1);
		pthread_detach(tid);
	}
	return (0);
}

int		start_process(t_state *state)
{
	int			i;
	void		*philo;

	state->start = get_time();
	i = 0;
	while (i < state->amount)
	{
		philo = (void*)(&state->philos[i]);
		state->philos[i].pid = fork();
		if (state->philos[i].pid < 0)
			return (1);
		else if (state->philos[i].pid == 0)
		{
			routine(&state->philos[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	return (0);
}

int		init_philos(t_state *state)
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
		state->philos[i].state = state;
		make_semaphore_name("SPhilo", (char*)semaphore, i);
		if ((state->philos[i].mutex = ft_sem_open(semaphore, 1)) < 0)
			return (1);
		make_semaphore_name("SEat", (char*)semaphore, i);
		if ((state->philos[i].eat_count_m = ft_sem_open(semaphore, 0)) < 0)
			return (1);
		i++;
	}
	return (0);
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
	if (!(state->philos =
		(t_philo*)malloc(sizeof(*(state->philos)) * state->amount)))
		return (1);
	if (init_philos(state))
		return (1);
	init_semaphores(state);
	return (0);
}
