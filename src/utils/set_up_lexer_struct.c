/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_lexer_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:28:18 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/22 18:32:15 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_up_lexer_struct(t_lexer *lexer, char *input)
{
	lexer->pos = 0;
	lexer->input = input;
	lexer->head = NULL;
}
