/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 11:53:57 by fulldemo          #+#    #+#             */
/*   Updated: 2020/05/15 10:15:46 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		main(int argc, char const **argv)
{
	t_state	state;

	if (check_arguments(argc, argv))
		return (exit_error("error: bad arguments\n"));
	if (init(&state, argc, argv))
	{
		clear_state(&state);
		return (exit_error("error: malloc failled\n"));
	}
	if (start_threads(&state))
	{
		clear_state(&state);
		return (exit_error("error: thread failled\n"));
	}
	pthread_mutex_lock(&state.somebody_dead_m);
	clear_state(&state);
	return (0);
}
