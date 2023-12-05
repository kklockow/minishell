/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:11:43 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/05 14:27:44 by fgabler          ###   ########.fr       */
/*   Created: 2023/11/11 12:23:17 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/01 07:38:07 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexing(t_lexer *lexer)
{
	if (lexer->process.time_to_lex == false)
		return (false);
	set_process_stat(&lexer->process, false, true, false);
	lexer->process.time_to_pars = true;
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
	/*
	t_lexer *tmp_lexer;

	tmp_lexer = lexer;
	while (tmp_lexer->head != NULL)
	{
		printf("\nstr:%s \ntoken_typ: %d\ntoken_len: %d\nnext: %p\n",
				tmp_lexer->head->str, tmp_lexer->head->type,
				tmp_lexer->head->token_len, tmp_lexer->head->next);
		tmp_lexer->head = tmp_lexer->head->next;
	}
	*/
	return (true);
}
