/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:18:09 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/13 13:43:34 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_up_parser_struct(t_parser **parser, t_cmd *command, t_lexer *lexer);

int	command_table(t_lexer *lexer, t_cmd *command)
{
	t_parser	*parser;

	if (lexer->process.time_to_pars == false)
		return (false);
	parser = NULL;
	set_up_parser_struct(&parser, command, lexer);
	syntax_check(parser);
	fill_command_struct(parser);
	//ist_grammar_correct== true
	//set_up_struct
	//
	lexer->process.time_to_exec = true;
	return (true);
}

static void	set_up_parser_struct(t_parser **parser, t_cmd *command, t_lexer *lexer)
{
	*parser = ft_calloc(1, sizeof(t_parser));
	(*parser)->command = command;
	(*parser)->lexer = lexer;
	(*parser)->error_accured = false;
}
