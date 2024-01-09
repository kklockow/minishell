/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:11:43 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/09 17:21:26 by fgabler          ###   ########.fr       */
/*   Created: 2023/11/11 12:23:17 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/01 07:38:07 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexing(t_lexer *lexer, t_process *process)
{
	if (process->time_to_lex == false)
		return (false);
	lexer->shell->process->time_to_pars = true;
	while (lexer->input[lexer->pos] != '\0' && time_to_lex(lexer) == true)
	{
		find_quote_pair(lexer);
		double_greater_and_smaler(lexer);
		get_single_tokens(lexer, '<');
		get_single_tokens(lexer, '>');
		get_single_tokens(lexer, '|');
		tag_word(lexer);
		skip_whitespace(lexer);
		lexer->set_token = false;
	}
	return (true);
}
