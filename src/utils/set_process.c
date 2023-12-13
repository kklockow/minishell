/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:20:32 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/05 14:24:51 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_process_stat(t_process *process, int lexer, int parser, int exec)
{
	process->time_to_lex = lexer;
	process->time_to_pars = parser;
	process->time_to_exec = exec;
}
