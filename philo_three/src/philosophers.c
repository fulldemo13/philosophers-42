/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 10:45:29 by fulldemo          #+#    #+#             */
/*   Updated: 2020/05/18 09:31:33 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_message(t_philo *philo, char *state)
{
	sem_wait(philo->state->write_m);
	ft_putnbr(get_time() - philo->state->start);
	write(1, "\t", 1);
	if (ft_strcmp("Counter must eat completed\n", state))
	{
		write(1, "Philosopher: ", 15);
		ft_putnbr(philo->position + 1);
	}
	write(1, state, ft_strlen(state));
	if (ft_strcmp("Counter must eat completed\n", state) &&
		ft_strcmp(" died\n", state))
		sem_post(philo->state->write_m);
}

void	philo_life(t_philo *philo)
{
	sem_wait(philo->state->forks_m);
	display_message(philo, " has taken a fork\n");
	sem_wait(philo->state->forks_m);
	display_message(philo, " has taken a fork\n");
	sem_wait(philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	display_message(philo, " is eating\n");
	usleep(philo->state->time_to_eat * 860);
	philo->eat_count++;
	philo->is_eating = 0;
	sem_post(philo->mutex);
	sem_post(philo->eat_count_m);
	display_message(philo, " is sleeping\n");
	sem_post(philo->state->forks_m);
	sem_post(philo->state->forks_m);
	usleep(philo->state->time_to_sleep * 860);
	display_message(philo, " is thinking\n");
}

void	*monitor_count(void *state_v)
{
	t_state *state;
	int		total;
	int		i;

	state = (t_state*)state_v;
	total = 0;
	while (total < state->must_eat_count)
	{
		i = 0;
		while (i < state->amount)
			sem_wait(state->philos[i++].eat_count_m);
		total++;
	}
	display_message(&state->philos[0], "Counter must eat completed\n");
	sem_post(state->somebody_dead_m);
	return ((void*)0);
}

void	*monitor_life(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		sem_wait(philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			display_message(philo, " died\n");
			sem_post(philo->mutex);
			sem_post(philo->state->somebody_dead_m);
			return ((void*)0);
		}
		sem_post(philo->mutex);
		usleep(1000);
	}
	return ((void*)0);
}

int		routine(t_philo *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo*)philo_v;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	if (pthread_create(&tid, NULL, &monitor_life, philo) != 0)
		return (1);
	pthread_detach(tid);
	while (1)
		philo_life(philo);
	return (0);
}
