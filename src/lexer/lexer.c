/*en ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:23:17 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/17 15:23:26 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(t_lexer *lexer, t_process *process)
{
	if (process->time_to_lex == false)
		return (false);

	while (input[i] != '\0')
	{
		quots_check(input, *data, &i);

	}
	return (0);
}
