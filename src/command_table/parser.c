/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:18:09 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/07 13:57:42 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_up_parser_struct(t_parser *parser, t_cmd *command, t_lexer *lexer);

int	parser(t_lexer *lexer, t_cmd *command)
{
	t_parser	parser;

	if (lexer->process.time_to_pars == false)
		return (false);
	set_up_parser_struct(&parser, command, lexer);
	syntax_check(&parser);
	//ist_grammar_correct== true
	//set_up_struct
	//
	return (true);
}

static void	set_up_parser_struct(t_parser *parser, t_cmd *command, t_lexer *lexer)
{
	parser->command = command;
	parser->lexer = lexer;

	parser->error_accured = false;
}
