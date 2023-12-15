/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:18:09 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/15 11:22:09 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_table(t_parser *parser)
{

	if (parser->lexer->shell->process->time_to_pars == false)
		return (false);
	syntax_check(parser);
	//expander
	fill_command_struct(parser);
	if (parser->error_accured == false)
		parser->shell->process->time_to_exec = true;
	return (true);
}
