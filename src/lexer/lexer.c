/*en ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:23:17 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/27 19:11:16 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexing(t_lexer *lexer)
{
	if (lexer->process.time_to_lex == false)
		return (false);
	while (lexer->input[lexer->pos] != '\0')
	{
		find_quote_pair(lexer);
		double_greater_and_smaler(lexer);
		get_single_tokens(lexer, '<');
		get_single_tokens(lexer, '>');
		get_single_tokens(lexer, '|');
		tag_word(lexer);
	}
	while (lexer->head != NULL)
	{
		printf("\nstr:%s \n", lexer->head->str);
		lexer->head = lexer->head->next;
	}
	return (true);
}
