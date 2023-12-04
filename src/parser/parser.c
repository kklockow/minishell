/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:18:09 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/04 13:53:59 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_lexer *lexer, t_cmd *command)
{
	if (lexer->process.time_to_pars == false)
		return (false);
	basic_gramma_check(lexer);
	(void) command;
	//ist_grammar_correct== true
	//set_up_struct
	//
	return (true);
}
