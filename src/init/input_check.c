/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:40:36 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/17 14:45:45 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_check(int ac, char **av, t_coordinate *coordinate)
{
	if (ac != 1)
	{
		ft_putstr_fd("ERROR: minishell takes·no input·parameter", 2);
		coordinate->run_loop = false;
	}
	else
	{
		coordinate->run_loop = true;
		coordinate->first_set_up = true;
	}
	(void) av;
}
