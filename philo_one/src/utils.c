/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 10:26:44 by fulldemo          #+#    #+#             */
/*   Updated: 2020/05/18 10:33:30 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int			check_arguments(int argc, char const **argv)
{
	int		i;
	int		j;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int			clear_state(t_state *state)
{
	int	i;

	if (state->forks_m)
	{
		i = 0;
		while (i < state->amount)
			pthread_mutex_destroy(&state->forks_m[i++]);
		free(state->forks_m);
	}
	if (state->philos)
	{
		i = 0;
		while (i < state->amount)
		{
			pthread_mutex_destroy(&state->philos[i].mutex);
			pthread_mutex_destroy(&state->philos[i++].eat_m);
		}
		free(state->philos);
	}
	pthread_mutex_destroy(&state->write_m);
	pthread_mutex_destroy(&state->somebody_dead_m);
	return (1);
}

int			exit_error(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

void		ft_putnbr(uint64_t n)
{
	unsigned int	nbr;

	if (n < 0)
	{
		ft_putchar('-');
		nbr = (unsigned int)(n * -1);
	}
	else
		nbr = (unsigned int)n;
	if (nbr >= 10)
		ft_putnbr(nbr / 10);
	ft_putchar((char)(nbr % 10 + 48));
}
