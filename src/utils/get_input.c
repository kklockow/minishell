/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:07:21 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/15 10:45:37 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(char **input, t_process *process)
{
	
	ft_bzero(process, sizeof(t_process));
	*input = readline("minishell> " );
	if (*input != NULL)
	{
		add_history(*input);
		(*process).time_to_setup = true;
	}
}
