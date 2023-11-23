/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_lexer_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:45:02 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/23 15:50:48 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_up_lexer_struct(t_lexer *lexer, char *input)
{
	lexer->pos = 0;
	lexer->input = input;
	lexer->head = NULL;
	lexer->process->time_to_lex = true;
	lexer->process->time_to_exec = false;
	lexer->process->time_to_pars = false;
}
