/*en ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:23:17 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/23 17:38:56 by fgabler          ###   ########.fr       */
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
		//greater_and_smaler_check(lexer);
	}
	return (0);
}
