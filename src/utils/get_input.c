/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:07:21 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/20 13:23:15 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(t_coordinate *coordinate)
{
	if (isatty(fileno(stdin)))
	{
		ft_bzero(&coordinate->process, sizeof(t_process));
		coordinate->input = readline("minishell> " );
		if (coordinate->input == NULL)
		{
			coordinate->run_loop = false;
			ft_bzero(&coordinate->process, sizeof(t_process));
			ft_putstr_fd("minishell> exit\n", 2);
		}
		else
		{
			add_history(coordinate->input);
			coordinate->process.time_to_setup = true;
		}
	}
	else
	{
		ft_bzero(&coordinate->process, sizeof(t_process));
		char *line;
		line = get_next_line(fileno(stdin));
		if (line == NULL)
		{
		coordinate->run_loop = false;
		coordinate->process.time_to_lex = false;
		ft_bzero(&coordinate->process, sizeof(t_process));
		return ;
		}
		else
		{
		//add_history(coordinate->input);
		coordinate->process.time_to_setup = true;
		}
		coordinate->input = ft_strtrim(line, "\n");
	}
}

/*
void	get_input(t_coordinate *coordinate)
{
	ft_bzero(&coordinate->process, sizeof(t_process));
	coordinate->input = readline("minishell> " );
	if (coordinate->input == NULL)
	{
		coordinate->run_loop = false;
		ft_bzero(&coordinate->process, sizeof(t_process));
		ft_putstr_fd("minishell> exit\n", 2);
	}
	else
	{
		add_history(coordinate->input);
		coordinate->process.time_to_setup = true;
}
*/
