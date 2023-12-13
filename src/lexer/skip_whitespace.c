/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 07:28:26 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/28 10:49:13 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(t_lexer *lexer)
{
	if (lexer->process.time_to_lex == false)
		return ;
	if (lexer->input[lexer->pos] == ' ')
		lexer->pos++;
}
