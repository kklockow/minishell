/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:20:32 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/15 09:44:47 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_processt_state(t_process *process, int set_up,
		int lexer,int parser, int exec)
{
	process->time_to_setup = set_up;
	process->time_to_lex = lexer;
	process->time_to_pars = parser;
	process->time_to_exec = exec;
}
