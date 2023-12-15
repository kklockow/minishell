/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:07:21 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/15 10:57:02 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(t_coordinate *coordinate)
{
	ft_bzero(&coordinate->process, sizeof(t_process));
	coordinate->input = readline("minishell> " );
	if (coordinate->input != NULL)
	{
		add_history(coordinate->input);
		coordinate->process.time_to_setup = true;
	}
}
