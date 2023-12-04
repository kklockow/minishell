/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:47:13 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/04 11:16:21 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_structs(t_cmd **command, t_lexer **lexer, t_process *process)
{
	if ((*process).time_to_setup == false)
		return (false);
	*command = ft_calloc(1, sizeof(t_cmd));
	if (command == NULL)
		return (false); //free
	*lexer = ft_calloc(1, sizeof(t_lexer));
	if (lexer == NULL)
		return (false); //free
	process = &(*lexer)->process;
	(*process).time_to_lex = true;
	return (true);
}
