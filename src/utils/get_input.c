/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:07:21 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/04 11:13:15 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(char *input, t_process *process)
{
	ft_bzero(process, sizeof(t_process));
	input = readline("minishell>" );
	if (input != NULL)
	{
		add_history(input);
		(*process).time_to_setup = true;
	}
}
