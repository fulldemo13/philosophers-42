/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 17:08:19 by fulldemo          #+#    #+#             */
/*   Updated: 2020/05/15 17:09:59 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		exit_error(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

int		check_arguments(int argc, char const **argv)
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

int		clear_state(t_state *state)
{
	int		i;
	char	semaphore[255];

	sem_unlink("SFork");
	sem_unlink("SWrite");
	sem_unlink("SDead");
	if (state->philos)
	{
		i = 0;
		while (i < state->amount)
		{
			make_semaphore_name("SPhilo", (char*)semaphore, i);
			sem_unlink(semaphore);
			make_semaphore_name("SEat", (char*)semaphore, i++);
			sem_unlink(semaphore);
		}
		free(state->philos);
	}
	return (1);
}

int		main(int argc, char const **argv)
{
	int		i;
	t_state	state;

	if (check_arguments(argc, argv))
		return (exit_error("error: bad arguments\n"));
	if (init(&state, argc, argv) || start_monitor_thread(&state)
		|| start_process(&state))
	{
		clear_state(&state);
		return (exit_error("error: fatal\n"));
	}
	sem_wait(state.somebody_dead_m);
	i = 0;
	while (i < state.amount)
		kill(state.philos[i++].pid, SIGKILL);
	clear_state(&state);
	return (0);
}
