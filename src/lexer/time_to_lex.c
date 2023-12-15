/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to_lex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:33:04 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/15 11:10:50 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	time_to_lex(t_lexer *lexer)
{
	if (lexer->shell->process->time_to_lex == true)
		return (true);
	return (false);
}
