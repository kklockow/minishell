/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:47:13 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/04 12:37:54 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_process(t_process *process, t_lexer **lexer);
static void	set_lexer(t_lexer **lexer, char *input);

int	setup_structs(t_cmd **command, t_lexer **lexer,
		t_process *process, char *input)
{
	if ((*process).time_to_setup == false)
		return (false);
	*command = ft_calloc(1, sizeof(t_cmd));
	if (command == NULL)
		return (false); //free
	*lexer = ft_calloc(1, sizeof(t_lexer));
	if (lexer == NULL)
		return (false); //free
	set_process(process, lexer);
	set_lexer(lexer, input);
	return (true);
}

static void	set_process(t_process *process, t_lexer **lexer)
{
	process = &(*lexer)->process;
	(*process).time_to_lex = true;
}

static void	set_lexer(t_lexer **lexer, char *input)
{
	(*lexer)->input = input;
}
