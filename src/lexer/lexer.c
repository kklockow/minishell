/*en ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:23:17 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/22 17:19:32 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(t_lexer *lexer, t_process *process)
{
	if (process->time_to_lex == false)
		return (false);
	lexer = malloc(sizeof(t_lexer));
	ft_bzero(lexer, sizeof(t_lexer));

	while (lexer->input[lexer->pos] != '\0')
	{
		find_quot_pair(lexer);
	}
	return (0);
}
