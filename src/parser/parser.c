/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:18:09 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/01 10:37:44 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_lexer *lexer, t_cmd *command)
{
	if (lexer->process.time_to_pars == false)
		return (false);
	(void) command;
	//ist_grammar_correct== true
	//set_up_struct
	//
	return (true);
}
