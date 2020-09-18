/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 19:54:46 by fulldemo          #+#    #+#             */
/*   Updated: 2020/05/18 10:35:30 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_message(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->state->write_m);
	ft_putnbr(get_time() - philo->state->start);
	write(1, ":\t", 2);
	if (ft_strcmp("Counter must eat completed\n", state))
	{
		write(1, "Philosopher: ", 15);
		ft_putnbr(philo->position + 1);
	}
	write(1, state, ft_strlen(state));
	pthread_mutex_unlock(&philo->state->write_m);
}

void	philo_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->forks_m[philo->lfork]);
	display_message(philo, " has taken a fork\n");
	pthread_mutex_lock(&philo->state->forks_m[philo->rfork]);
	display_message(philo, " has taken a fork\n");
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	display_message(philo, " is eating\n");
	usleep(philo->state->time_to_eat * 860);
	philo->eat_count++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->eat_m);
	display_message(philo, " is sleeping\n");
	pthread_mutex_unlock(&philo->state->forks_m[philo->lfork]);
	pthread_mutex_unlock(&philo->state->forks_m[philo->rfork]);
	usleep(philo->state->time_to_sleep * 860);
	display_message(philo, " is thinking\n");
}

void	*monitor_count(void *state_v)
{
	t_state *state;
	int		i;
	int		total;

	state = (t_state*)state_v;
	total = 0;
	while (total < state->must_eat_count)
	{
		i = 0;
		while (i < state->amount)
			pthread_mutex_lock(&state->philos[i++].eat_m);
		total++;
	}
	display_message(&state->philos[0], "Counter must eat completed\n");
	pthread_mutex_lock(&state->write_m);
	pthread_mutex_unlock(&state->somebody_dead_m);
	return ((void*)0);
}

void	*monitor_life(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			display_message(philo, " died\n");
			pthread_mutex_lock(&philo->state->write_m);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->state->somebody_dead_m);
			return ((void*)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
}

void	*start_life(void *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo*)philo_v;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	if (pthread_create(&tid, NULL, &monitor_life, philo_v) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
		philo_life(philo);
	return ((void*)0);
}
