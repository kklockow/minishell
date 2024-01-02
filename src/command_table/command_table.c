/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:18:09 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/02 17:05:24 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_table(t_parser *parser, t_process *process)
{
	if (process->time_to_pars == false)
		return (false);
	syntax_check(parser);
	expand(parser);
	fill_command_struct(parser);
	if (parser->error_accured == false)
		parser->shell->process->time_to_exec = true;
	return (true);
}
